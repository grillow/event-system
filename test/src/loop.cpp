#include <gtest/gtest.h>

#include <GES/GES.hpp>

#include <functional>


struct LoopIterationEvent : IEventTemplate<LoopIterationEvent> {
    using condition_t = std::function<bool(LoopIterationEvent &)>;
    using iteration_t = std::function<void(LoopIterationEvent &)>;
    
    LoopIterationEvent(
                std::shared_ptr<EventBus> bus,
                condition_t condition,
                iteration_t iteration
            )
            : bus(bus), condition(condition), iteration(iteration) {
    }

    ~LoopIterationEvent() {
        if (condition(*this)) {
            iteration(*this);
            bus->Raise<LoopIterationEvent>(bus, condition, iteration);
        }
    }

private:
    std::shared_ptr<EventBus> bus;
    const condition_t condition;
    const iteration_t iteration;
};
template<>
const IEvent::Type_t IEventTemplate<LoopIterationEvent>::ID = 1;


TEST(Loop, simple) {
    const size_t first_i = 5;
    const size_t last_i = 10;

    // true modern C++ for loop
    auto bus = EventBus::Create();

    size_t events_created = 0;
    size_t iteration_called = 0;

    size_t i = first_i;
    size_t sum = 0;

    auto handle = bus->Add(std::make_unique<IEventListenerLambda<LoopIterationEvent>>(
        [&](LoopIterationEvent & event) {
            ++events_created;
        }
    ));

    bus->Raise<LoopIterationEvent>(
        bus,
        [&i](LoopIterationEvent & event) {
            return i < last_i;
        },
        [&i, &sum, &iteration_called](LoopIterationEvent & event) {
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

