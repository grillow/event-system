#include <gtest/gtest.h>

#include "example.hpp"


TEST(Example, example) {
    std::shared_ptr<EventBus> bus = EventBus::Create();
    ExampleStruct sample;
    sample.Register(bus);
    bus->Raise(std::make_unique<ExampleEvent>(1337));
    bus->Raise(std::make_unique<ExampleEvent>(1488));

    EXPECT_EQ(global_number, 1337 + 1337 + 1488 + 1488);
}

