#include <gtest/gtest.h>

#include <GES/GES.hpp>

namespace Event {
    struct Number : IEventTemplate<Number> {
        Number(int64_t number) : number(number) {}
        int64_t number;
    };
    template<> const IEvent::Type_t IEventTemplate<Number>::ID = "Number"_t;
}

TEST(Priority, hook) {
    auto bus = EventBus::Create();
	
	int64_t number = 0;

    // victim
    auto receivehandle = bus->Add<EventListenerLambda<Event::Number>>(
        [&](Event::Number & event) -> void {
            number = event.number;
        }
    );

	EXPECT_EQ(number, 0);
	
	bus->Raise<Event::Number>(1337);
	EXPECT_EQ(number, 1337);

    // hook
    auto hookhandle = bus->Add<EventListenerLambda<Event::Number>>(
        Priority::HOOK,
        [](Event::Number & event) {
            event.number = -event.number;
        }
    );

	bus->Raise<Event::Number>(1337);
	EXPECT_EQ(number, -1337);
}

