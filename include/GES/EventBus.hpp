#pragma once
#include "IEvent.hpp"
#include "IEventListener.hpp"
#include "EventListenerHandle.hpp"

#include <memory>

struct EventBus final : public std::enable_shared_from_this<EventBus> {
public:
    EventBus();
    ~EventBus();

    EventBus(const EventBus & other) = delete;

    void Raise(std::unique_ptr<IEvent> event);

    [[nodiscard]] EventListenerHandle Add(std::unique_ptr<IEventListenerBase> listener);
    void Remove(EventListenerHandle && handle);

private:
    struct Impl;
    std::unique_ptr<EventBus::Impl> m_pimpl;
};

