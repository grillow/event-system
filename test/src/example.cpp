#include <gtest/gtest.h>

#include "example.hpp"

#include <iostream>
TEST(Example, BirthStats) {
    int *arr = new int[10];
    arr[0] = 1337;
    std::cout << arr[0];
    
    std::shared_ptr<EventBus> bus = EventBus::Create();
    
    std::shared_ptr<PopulationStats> stats(
		    std::make_shared<PopulationStats>());
    
    {
        PopulationListenerHandler handler(bus, stats);
        
       
        EXPECT_EQ(stats->GetPopulation(), 0);
        
        bus->Raise(std::make_unique<BirthEvent>("First"));
        
        EXPECT_EQ(stats->GetPopulation(), 1);
        
        bus->Raise(std::make_unique<BirthEvent>("Second"));
        
        EXPECT_EQ(stats->GetPopulation(), 2);
        
        bus->Raise(std::make_unique<BirthEvent>("Third"));
        
        EXPECT_EQ(stats->GetPopulation(), 3);
    }

    bus->Raise(std::make_unique<BirthEvent>("Fourth"));

    EXPECT_EQ(stats->GetPopulation(), 3);
}

/*
TEST(Example, example) {
    std::shared_ptr<EventBus> bus = EventBus::Create();
    
    std::shared_ptr<PopulationStats> stats(
		    std::make_shared<PopulationStats>());
    
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
*/

