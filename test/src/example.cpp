#include <gtest/gtest.h>

#include "example.hpp"

template<>
const std::string IEventTemplate<BirthEvent>::Name = "BirthEvent";
template<>
const std::string IEventTemplate<DeathEvent>::Name = "DeathEvent";


TEST(Example, example) {
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

