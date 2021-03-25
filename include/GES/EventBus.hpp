#pragma once
#include "IEvent.hpp"
#include "IEventListener.hpp"
#include "EventListenerHandle.hpp"

#include <memory>

struct EventBus final {

public:
    EventBus(std::unique_ptr<EventBus::Impl> impl); // could not manage to make it private
    
    static std::shared_ptr<EventBus> Create();

    ~EventBus();

    EventBus(const EventBus & other) = delete;

    void Raise(std::unique_ptr<IEvent> event);

    [[nodiscard]] EventListenerHandle Add(std::unique_ptr<IEventListenerBase> listener);
    void Remove(EventListenerHandle && handle);

private:
    struct Impl;

private:

    std::unique_ptr<EventBus::Impl> m_pimpl;
};

