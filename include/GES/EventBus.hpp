#pragma once
#include "IEvent.hpp"
#include "IEventListener.hpp"
#include "EventListenerHandle.hpp"

#include <memory>
#include <typeindex>
#include <unordered_map>
#include <list>

struct EventBus final {
public:
    EventBus();
    ~EventBus() = default;

    EventBus(const EventBus & other) = delete;

    void Dispatch(const IEvent & event);

    EventListenerHandle Add(std::unique_ptr<IEventListenerBase> listener);
    void Remove(const EventListenerHandle & handle);

private:
    struct Impl;
    std::unique_ptr<EventBus::Impl> m_pimpl;
};

