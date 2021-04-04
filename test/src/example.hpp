#pragma once
#include <GES/GES.hpp>

#include <string>

namespace Event {
    struct Birth : IEventTemplate<Birth> {
        explicit Birth(std::string name) : m_name(std::move(name)) {}
        std::string m_name;
    };
    struct Death : IEventTemplate<Death> {
        explicit Death(std::string name) : m_name(std::move(name)) {}
        std::string m_name;
    };
}

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
    IEventListener<Event::Birth>,
    IEventListener<Event::Death> {

    PopulationListener(std::weak_ptr<PopulationStats> stats) :
        m_stats(stats) {}

    void OnEvent(Event::Birth & event) {
        if (auto stats = m_stats.lock()) {
            stats->IncreasePopulation();
        }
    }

    void OnEvent(Event::Death & event) {
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
    IEventListenerLambda<Event::Birth>,
    IEventListenerLambda<Event::Death> {
    
    PopulationListenerLambda(
                IEventListenerResource::callback_t<Event::Birth> callback_birth,
                IEventListenerResource::callback_t<Event::Death> callback_death) :
            IEventListenerLambda<Event::Birth>(callback_birth),
            IEventListenerLambda<Event::Death>(callback_death)
        {}
};

struct PopulationListenerLambdaHandler {
    PopulationListenerLambdaHandler(std::shared_ptr<EventBus> bus,
            IEventListenerResource::callback_t<Event::Birth> callback_birth,
            IEventListenerResource::callback_t<Event::Death> callback_death) {
        handler.Subscribe(bus, std::make_unique<PopulationListenerLambda>(
            callback_birth, callback_death
        ));
    }
private:
	Handler handler;
};

