#pragma once
#include <GES/GES.hpp>

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


struct PopulationListenerHandler {
    PopulationListenerHandler(std::shared_ptr<EventBus> bus,
            std::weak_ptr<PopulationStats> stats) {
        handler.Subscribe(bus, std::make_unique<PopulationListener>(stats));
    }
private:
	Handler handler;
};

struct PopulationListenerLambda :
    IEventListenerLambda<BirthEvent>,
    IEventListenerLambda<DeathEvent> {
    
    PopulationListenerLambda(
                IEventListenerResource::callback_t<BirthEvent> callback_birth,
                IEventListenerResource::callback_t<DeathEvent> callback_death) :
            IEventListenerLambda<BirthEvent>(callback_birth),
            IEventListenerLambda<DeathEvent>(callback_death)
        {}
};

struct PopulationListenerLambdaHandler {
    PopulationListenerLambdaHandler(std::shared_ptr<EventBus> bus,
            IEventListenerResource::callback_t<BirthEvent> callback_birth,
            IEventListenerResource::callback_t<DeathEvent> callback_death) {
        handler.Subscribe(bus, std::make_unique<PopulationListenerLambda>(
            callback_birth, callback_death
        ));
    }
private:
	Handler handler;
};

