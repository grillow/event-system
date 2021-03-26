#include <gtest/gtest.h>

#include <GES/EventBus.hpp>

struct AddEvent : IEvent {
    static const std::string Name;
    std::string Type() const override {
	return Name;
    }

    AddEvent(int64_t number) : number(number) {}
    const int64_t number;
};
const std::string AddEvent::Name = "SimpleEvent";


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
    bus->Raise(std::make_unique<AddEvent>(1337));
    EXPECT_EQ(number, 1337);

    bus->Raise(std::make_unique<AddEvent>(-1337));
    EXPECT_EQ(number, 0);

    bus->Raise(std::make_unique<AddEvent>(200));
    EXPECT_EQ(number, 200);
    
    bus->Raise(std::make_unique<AddEvent>(800));
    EXPECT_EQ(number, 1000);
}

