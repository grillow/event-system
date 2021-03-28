#include <gtest/gtest.h>

#include <GES/EventBus.hpp>

#include <iostream>
#include <array>


struct EmptyEvent : IEventTemplate<EmptyEvent> {};
template<> const std::string IEventTemplate<EmptyEvent>::Name = "EmptyEvent";


TEST(id, uniqueness) {
    std::array<bool, 3> called = { false };
    const auto callback0 = [&called](EmptyEvent &) { called[0] = true; };
    const auto callback1 = [&called](EmptyEvent &) { called[1] = true; };
    const auto callback2 = [&called](EmptyEvent &) { called[2] = true; };
    const auto reset = [&called](){ for ( auto & e : called ) { e = false; } };

    auto bus = EventBus::Create();

    auto handle_0 = bus->Add(std::make_unique<IEventListenerLambda<EmptyEvent>>(callback0));
    auto handle_1 = bus->Add(std::make_unique<IEventListenerLambda<EmptyEvent>>(callback1));
    
    reset();
    bus->Raise(std::make_unique<EmptyEvent>());
    EXPECT_EQ(called[0], true); EXPECT_EQ(called[1], true); EXPECT_EQ(called[2], false);
    reset();

    {
        handle_0.Release();
        auto handle_2 = bus->Add(std::make_unique<IEventListenerLambda<EmptyEvent>>(callback2));
        bus->Raise(std::make_unique<EmptyEvent>());
        EXPECT_EQ(called[0], false); EXPECT_EQ(called[1], true); EXPECT_EQ(called[2], true);
        reset();
    }

    bus->Raise(std::make_unique<EmptyEvent>());
    EXPECT_EQ(called[0], false); EXPECT_EQ(called[1], true); EXPECT_EQ(called[2], false);
    reset();

    auto handle_0_new = bus->Add(std::make_unique<IEventListenerLambda<EmptyEvent>>(callback0));
    auto handle_2 = bus->Add(std::make_unique<IEventListenerLambda<EmptyEvent>>(callback2));
    bus->Raise(std::make_unique<EmptyEvent>());
    EXPECT_EQ(called[0], true); EXPECT_EQ(called[1], true); EXPECT_EQ(called[2], true);
    reset();

    handle_1.Release();
    bus->Raise(std::make_unique<EmptyEvent>());
    EXPECT_EQ(called[0], true); EXPECT_EQ(called[1], false); EXPECT_EQ(called[2], true);
    reset();

    handle_2.Release();
    auto handle_2_new = bus->Add(std::make_unique<IEventListenerLambda<EmptyEvent>>(callback2));
    bus->Raise(std::make_unique<EmptyEvent>());
    EXPECT_EQ(called[0], true); EXPECT_EQ(called[1], false); EXPECT_EQ(called[2], true);

}

