#include <gtest/gtest.h>

#include "example.hpp"

namespace EventType {
    enum EventType : IEvent::Type_t {
        BirthEvent,
        DeathEvent
    };
}

template<>
const IEvent::Type_t IEventTemplate<BirthEvent>::ID = EventType::BirthEvent;
template<>
const IEvent::Type_t IEventTemplate<DeathEvent>::ID = EventType::DeathEvent;


TEST(Example, ordinary) {
    auto bus = EventBus::Create();
    
    auto stats = std::make_shared<PopulationStats>();
   
    { 
        PopulationListenerHandler handler(bus, stats);

        EXPECT_EQ(stats->GetPopulation(), 0);

        bus->Raise(std::make_unique<BirthEvent>("First"));

        EXPECT_EQ(stats->GetPopulation(), 1);

        bus->Raise(std::make_unique<BirthEvent>("Second"));

        EXPECT_EQ(stats->GetPopulation(), 2);

        bus->Raise(std::make_unique<DeathEvent>("Second"));

        EXPECT_EQ(stats->GetPopulation(), 1);

        bus->Raise(std::make_unique<BirthEvent>("Third"));

        EXPECT_EQ(stats->GetPopulation(), 2);

        bus->Raise(std::make_unique<DeathEvent>("First"));

        EXPECT_EQ(stats->GetPopulation(), 1);

        bus->Raise(std::make_unique<DeathEvent>("Third"));

        EXPECT_EQ(stats->GetPopulation(), 0);
    }

    bus->Raise(std::make_unique<BirthEvent>("Fourth"));
    EXPECT_EQ(stats->GetPopulation(), 0);

}


TEST(Example, lambda) {
    auto bus = EventBus::Create();
    
    auto stats = std::make_shared<PopulationStats>();
   
    { 
        PopulationListenerLambdaHandler handler(bus,
                [&](BirthEvent & event) {
                    stats->IncreasePopulation();
                },
                [&](DeathEvent & event) {
                    stats->DecreasePopulation();
                }
        );

        EXPECT_EQ(stats->GetPopulation(), 0);

        bus->Raise(std::make_unique<BirthEvent>("First"));

        EXPECT_EQ(stats->GetPopulation(), 1);

        bus->Raise(std::make_unique<BirthEvent>("Second"));

        EXPECT_EQ(stats->GetPopulation(), 2);

        bus->Raise(std::make_unique<DeathEvent>("Second"));

        EXPECT_EQ(stats->GetPopulation(), 1);

        bus->Raise(std::make_unique<BirthEvent>("Third"));

        EXPECT_EQ(stats->GetPopulation(), 2);

        bus->Raise(std::make_unique<DeathEvent>("First"));

        EXPECT_EQ(stats->GetPopulation(), 1);

        bus->Raise(std::make_unique<DeathEvent>("Third"));

        EXPECT_EQ(stats->GetPopulation(), 0);
    }

    bus->Raise(std::make_unique<BirthEvent>("Fourth"));
    EXPECT_EQ(stats->GetPopulation(), 0);

}

