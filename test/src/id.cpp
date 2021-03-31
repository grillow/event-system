#include <gtest/gtest.h>

#include <GES/GES.hpp>

#include <iostream>
#include <array>


struct EmptyEvent : IEventTemplate<EmptyEvent> {};
template<> const IEvent::Type_t IEventTemplate<EmptyEvent>::ID = 1;


TEST(id, uniqueness) {
    std::array<bool, 3> called = { false };
    const auto callback0 = [&called](EmptyEvent &) { called[0] = true; };
    const auto callback1 = [&called](EmptyEvent &) { called[1] = true; };
    const auto callback2 = [&called](EmptyEvent &) { called[2] = true; };
    const auto reset = [&called](){ for ( auto & e : called ) { e = false; } };

    auto bus = EventBus::Create();

    auto handle_0 = bus->Add<IEventListenerLambda<EmptyEvent>>(callback0);
    auto handle_1 = bus->Add<IEventListenerLambda<EmptyEvent>>(callback1);
    
    reset();
    bus->Raise<EmptyEvent>();
    EXPECT_EQ(called[0], true); EXPECT_EQ(called[1], true); EXPECT_EQ(called[2], false);
    reset();

    {
        handle_0.Release();
        auto handle_2 = bus->Add(std::make_unique<IEventListenerLambda<EmptyEvent>>(callback2));
        bus->Raise<EmptyEvent>();
        EXPECT_EQ(called[0], false); EXPECT_EQ(called[1], true); EXPECT_EQ(called[2], true);
        reset();
    }

    bus->Raise<EmptyEvent>();
    EXPECT_EQ(called[0], false); EXPECT_EQ(called[1], true); EXPECT_EQ(called[2], false);
    reset();

    handle_0 = bus->Add(std::make_unique<IEventListenerLambda<EmptyEvent>>(callback0));
    auto handle_2 = bus->Add(std::make_unique<IEventListenerLambda<EmptyEvent>>(callback2));
    bus->Raise<EmptyEvent>();
    EXPECT_EQ(called[0], true); EXPECT_EQ(called[1], true); EXPECT_EQ(called[2], true);
    reset();

    handle_1.Release();
    bus->Raise<EmptyEvent>();
    EXPECT_EQ(called[0], true); EXPECT_EQ(called[1], false); EXPECT_EQ(called[2], true);
    reset();

    handle_2 = bus->Add(std::make_unique<IEventListenerLambda<EmptyEvent>>(callback2));
    bus->Raise<EmptyEvent>();
    EXPECT_EQ(called[0], true); EXPECT_EQ(called[1], false); EXPECT_EQ(called[2], true);

}

