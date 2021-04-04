#include <gtest/gtest.h>

#include "example.hpp"


template<>
const IEvent::Type_t IEventTemplate<Event::Birth>::ID = "Birth"_t;
template<>
const IEvent::Type_t IEventTemplate<Event::Death>::ID = "Death"_t;


TEST(Example, ordinary) {
    auto bus = EventBus::Create();
    
    auto stats = std::make_shared<PopulationStats>();
   
    { 
        PopulationListenerHandler handler(bus, stats);

        EXPECT_EQ(stats->GetPopulation(), 0);

        bus->Raise<Event::Birth>("First");

        EXPECT_EQ(stats->GetPopulation(), 1);

        bus->Raise<Event::Birth>("Second");

        EXPECT_EQ(stats->GetPopulation(), 2);

        bus->Raise<Event::Death>("Second");

        EXPECT_EQ(stats->GetPopulation(), 1);

        bus->Raise<Event::Birth>("Third");

        EXPECT_EQ(stats->GetPopulation(), 2);

        bus->Raise<Event::Death>("First");

        EXPECT_EQ(stats->GetPopulation(), 1);

        bus->Raise<Event::Death>("Third");

        EXPECT_EQ(stats->GetPopulation(), 0);
    }

    bus->Raise<Event::Birth>("Fourth");
    EXPECT_EQ(stats->GetPopulation(), 0);

}

