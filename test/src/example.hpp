#include <GES/EventBus.hpp>
#include <GES/Subscriber.hpp>

#include <string>
//#include <iostream>

struct BirthEvent : IEventTemplate<BirthEvent> {
    explicit BirthEvent(std::string name) : m_name(std::move(name)) {}
    std::string m_name;
};
template<>
const std::string IEventTemplate<BirthEvent>::Name = "BirthEvent";


struct DeathEvent : IEventTemplate<DeathEvent> {
    explicit DeathEvent(std::string name) : m_name(std::move(name)) {}
    std::string m_name;
};
template<>
const std::string IEventTemplate<DeathEvent>::Name = "DeathEvent";


struct PopulationStats {
    PopulationStats() : m_population(0) {}

    size_t GetPopulation() const {
        return m_population;
    }

    size_t IncreasePopulation() {
        return ++m_population;
    }

    size_t DecreasePopulation() {
        return --m_population;
    }

private:
    size_t m_population;

};


struct PopulationListener :
    IEventListener<BirthEvent>/*,
    IEventListener<DeathEvent>*/ {

    PopulationListener(std::weak_ptr<PopulationStats> stats) :
        m_stats(stats) {}

    void OnEvent(BirthEvent & event) {
        //std::cout << event.m_name << " has been born!" << std::endl;
        if (auto stats = m_stats.lock()) {
            stats->IncreasePopulation();
        }
    }

    /*void OnEvent(DeathEvent & event) {
    //std::cout << event.m_name << " has died!" << std::endl;
    if (auto stats = m_stats.lock()) {
    stats->DecreasePopulation();
    }
    }*/

private:
    std::weak_ptr<PopulationStats> m_stats;
};


struct PopulationListenerHandler : Subscriber{
    PopulationListenerHandler(std::shared_ptr<EventBus> bus,
            std::weak_ptr<PopulationStats> stats) {
        Subscribe(bus, std::make_unique<PopulationListener>(stats));
    }
};

