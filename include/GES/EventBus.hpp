#pragma once
#include "IEvent.hpp"
#include "IEventListener.hpp"
#include "EventListenerHandle.hpp"

#include <memory>

struct EventBus final {
public:
    EventBus();
    ~EventBus();

    EventBus(const EventBus & other) = delete;

    void Dispatch(IEvent & event);

    EventListenerHandle Add(std::unique_ptr<IEventListenerBase> listener);
    void Remove(EventListenerHandle && handle);

private:
    struct Impl;
    std::unique_ptr<EventBus::Impl> m_pimpl;
};

