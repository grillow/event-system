#include <gtest/gtest.h>

#include <GES/EventBus.hpp>
#include <GES/Handler.hpp>

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
            bus->Raise(std::make_unique<LoopIterationEvent>(bus, condition, iteration));
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

    size_t called = 0;

    size_t i = first_i;
    size_t sum = 0;

    auto handle = bus->Add(std::make_unique<IEventListenerLambda<LoopIterationEvent>>(
        [&](LoopIterationEvent & event) {
            ++called;
        }
    ));

    bus->Raise(std::make_unique<LoopIterationEvent>(
        bus,
        [&i](LoopIterationEvent & event) {
            return i < last_i;
        },
        [&i, &sum](LoopIterationEvent & event) {
            sum += i;
            ++i;
        }
    ));

    // equivalent
    size_t sum_check = 0;
    for (size_t i = first_i; i < last_i; ++i) {
        sum_check += i;
    }

    // check
    EXPECT_EQ(called, last_i - first_i + 1);
    EXPECT_EQ(sum, sum_check);

}

