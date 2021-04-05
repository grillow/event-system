#include <gtest/gtest.h>

#include <GES/GES.hpp>

namespace Event {
    struct Add : EventTemplate<Add> {
        Add(int64_t number) : number(number) {}
        const int64_t number;
    };
    template<> const IEvent::Type_t EventTemplate<Add>::ID = "Add"_t;
}

TEST(Lambda, simple) {
    std::shared_ptr<Event::Bus> bus = Event::Bus::Create();
    int64_t number = 0;

    auto handle1 = bus->Add(
	std::make_unique<Event::Listener<Event::Add>>(
	    [&](Event::Add & event) -> void {
		    number += event.number;
	    }
    ));

    EXPECT_EQ(number, 0);

	bus->Raise<Event::Add>(1337);
    EXPECT_EQ(number, 1337);

    bus->Raise<Event::Add>(-1337);
    EXPECT_EQ(number, 0);

    bus->Raise<Event::Add>(200);
    EXPECT_EQ(number, 200);
    
    bus->Raise<Event::Add>(800);
    EXPECT_EQ(number, 1000);
}

