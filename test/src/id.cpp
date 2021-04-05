#include <gtest/gtest.h>

#include <GES/GES.hpp>

#include <iostream>
#include <array>

namespace Event {
    struct Empty : EventTemplate<Empty> {};
    template<> const IEvent::Type_t EventTemplate<Empty>::ID = "Empty"_t;
}

TEST(id, uniqueness) {
    std::array<bool, 3> called = { false };
    const auto callback0 = [&called](Event::Empty &) { called[0] = true; };
    const auto callback1 = [&called](Event::Empty &) { called[1] = true; };
    const auto callback2 = [&called](Event::Empty &) { called[2] = true; };
    const auto reset = [&called](){ for ( auto & e : called ) { e = false; } };

    auto bus = Event::Bus::Create();

    auto handle_0 = bus->Add<Event::Listener<Event::Empty>>(callback0);
    auto handle_1 = bus->Add<Event::Listener<Event::Empty>>(callback1);
    
    reset();
    bus->Raise<Event::Empty>();
    EXPECT_EQ(called[0], true); EXPECT_EQ(called[1], true); EXPECT_EQ(called[2], false);
    reset();

    {
        handle_0.Release();
        auto handle_2 = bus->Add<Event::Listener<Event::Empty>>(callback2);
        bus->Raise<Event::Empty>();
        EXPECT_EQ(called[0], false); EXPECT_EQ(called[1], true); EXPECT_EQ(called[2], true);
        reset();
    }

    bus->Raise<Event::Empty>();
    EXPECT_EQ(called[0], false); EXPECT_EQ(called[1], true); EXPECT_EQ(called[2], false);
    reset();

    handle_0 = bus->Add<Event::Listener<Event::Empty>>(callback0);
    auto handle_2 = bus->Add<Event::Listener<Event::Empty>>(callback2);
    bus->Raise<Event::Empty>();
    EXPECT_EQ(called[0], true); EXPECT_EQ(called[1], true); EXPECT_EQ(called[2], true);
    reset();

    handle_1.Release();
    bus->Raise<Event::Empty>();
    EXPECT_EQ(called[0], true); EXPECT_EQ(called[1], false); EXPECT_EQ(called[2], true);
    reset();

    handle_2 = bus->Add<Event::Listener<Event::Empty>>(callback2);
    bus->Raise<Event::Empty>();
    EXPECT_EQ(called[0], true); EXPECT_EQ(called[1], false); EXPECT_EQ(called[2], true);

}

