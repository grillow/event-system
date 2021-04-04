#include <gtest/gtest.h>

#include "example.hpp"


template<>
const IEvent::Type_t IEventTemplate<BirthEvent>::ID = "BirthEvent"_t;
template<>
const IEvent::Type_t IEventTemplate<DeathEvent>::ID = "DeathEvent"_t;


TEST(Example, ordinary) {
    auto bus = EventBus::Create();
    
    auto stats = std::make_shared<PopulationStats>();
   
    { 
        PopulationListenerHandler handler(bus, stats);

        EXPECT_EQ(stats->GetPopulation(), 0);

        bus->Raise<BirthEvent>("First");

        EXPECT_EQ(stats->GetPopulation(), 1);

        bus->Raise<BirthEvent>("Second");

        EXPECT_EQ(stats->GetPopulation(), 2);

        bus->Raise<DeathEvent>("Second");

        EXPECT_EQ(stats->GetPopulation(), 1);

        bus->Raise<BirthEvent>("Third");

        EXPECT_EQ(stats->GetPopulation(), 2);

        bus->Raise<DeathEvent>("First");

        EXPECT_EQ(stats->GetPopulation(), 1);

        bus->Raise<DeathEvent>("Third");

        EXPECT_EQ(stats->GetPopulation(), 0);
    }

    bus->Raise<BirthEvent>("Fourth");
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

        bus->Raise<BirthEvent>("First");

        EXPECT_EQ(stats->GetPopulation(), 1);

        bus->Raise<BirthEvent>("Second");

        EXPECT_EQ(stats->GetPopulation(), 2);

        bus->Raise<DeathEvent>("Second");

        EXPECT_EQ(stats->GetPopulation(), 1);

        bus->Raise<BirthEvent>("Third");

        EXPECT_EQ(stats->GetPopulation(), 2);

        bus->Raise<DeathEvent>("First");

        EXPECT_EQ(stats->GetPopulation(), 1);

        bus->Raise<DeathEvent>("Third");

        EXPECT_EQ(stats->GetPopulation(), 0);
    }

    bus->Raise<BirthEvent>("Fourth");
    EXPECT_EQ(stats->GetPopulation(), 0);

}

