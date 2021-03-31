#include <gtest/gtest.h>

#include <GES/GES.hpp>


struct AddEvent : IEventTemplate<AddEvent> {
    AddEvent(int64_t number) : number(number) {}
    const int64_t number;
};
template<> const IEvent::Type_t IEventTemplate<AddEvent>::ID = 1;


TEST(Lambda, simple) {
    std::shared_ptr<EventBus> bus = EventBus::Create();
    int64_t number = 0;

    auto handle1 = bus->Add(
	std::make_unique<IEventListenerLambda<AddEvent>>(
	    [&](AddEvent & event) -> void {
		    number += event.number;
	    }
    ));

    EXPECT_EQ(number, 0);

	bus->Raise<AddEvent>(1337);
    EXPECT_EQ(number, 1337);

    bus->Raise<AddEvent>(-1337);
    EXPECT_EQ(number, 0);

    bus->Raise<AddEvent>(200);
    EXPECT_EQ(number, 200);
    
    bus->Raise<AddEvent>(800);
    EXPECT_EQ(number, 1000);
}

