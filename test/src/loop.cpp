#include <gtest/gtest.h>

#include <GES/GES.hpp>

#include <functional>


namespace Event {
    struct LoopIteration : EventTemplate<LoopIteration> {
        using condition_t = std::function<bool(LoopIteration &)>;
        using iteration_t = std::function<void(LoopIteration &)>;
        
        LoopIteration(
                    std::shared_ptr<EventBus> bus,
                    condition_t condition,
                    iteration_t iteration
                )
                : bus(bus), condition(condition), iteration(iteration) {
        }

        ~LoopIteration() {
            if (condition(*this)) {
                iteration(*this);
                bus->Raise<LoopIteration>(bus, condition, iteration);
            }
        }

    private:
        std::shared_ptr<EventBus> bus;
        const condition_t condition;
        const iteration_t iteration;
    };
    template<>
    const IEvent::Type_t EventTemplate<LoopIteration>::ID = "LoopIteration"_t;
}


TEST(Loop, simple) {
    const size_t first_i = 5;
    const size_t last_i = 10;

    // true modern C++ for loop
    auto bus = EventBus::Create();

    size_t events_created = 0;
    size_t iteration_called = 0;

    size_t i = first_i;
    size_t sum = 0;

    auto handle = bus->Add<EventListenerLambda<Event::LoopIteration>>(
        [&](Event::LoopIteration & event) {
            ++events_created;
        }
    );

    bus->Raise<Event::LoopIteration>(
        bus,
        [&i](Event::LoopIteration & event) {
            return i < last_i;
        },
        [&i, &sum, &iteration_called](Event::LoopIteration & event) {
            ++iteration_called;
            sum += i;
            ++i;
        }
    );

    // equivalent
    size_t sum_check = 0;
    for (size_t i = first_i; i < last_i; ++i) {
        sum_check += i;
    }

    // check
    EXPECT_EQ(events_created,   last_i - first_i + 1);
    EXPECT_EQ(iteration_called, last_i - first_i);
    EXPECT_EQ(sum, sum_check);

}

