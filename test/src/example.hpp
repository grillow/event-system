#pragma once
#include <GES/EventBus.hpp>
#include <GES/Handler.hpp>

#include <string>


struct BirthEvent : IEventTemplate<BirthEvent> {
    explicit BirthEvent(std::string name) : m_name(std::move(name)) {}
    std::string m_name;
};
struct DeathEvent : IEventTemplate<DeathEvent> {
    explicit DeathEvent(std::string name) : m_name(std::move(name)) {}
    std::string m_name;
};


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
    IEventListener<BirthEvent>,
    IEventListener<DeathEvent> {

    PopulationListener(std::weak_ptr<PopulationStats> stats) :
        m_stats(stats) {}

    void OnEvent(BirthEvent & event) {
        if (auto stats = m_stats.lock()) {
            stats->IncreasePopulation();
        }
    }

    void OnEvent(DeathEvent & event) {
        if (auto stats = m_stats.lock()) {
            stats->DecreasePopulation();
        }
    }

private:
    std::weak_ptr<PopulationStats> m_stats;
};


struct PopulationListenerHandler : Handler {
    PopulationListenerHandler(std::shared_ptr<EventBus> bus,
            std::weak_ptr<PopulationStats> stats) {
        Subscribe(bus, std::make_unique<PopulationListener>(stats));
    }
};

