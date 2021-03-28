#pragma once
#include "IEvent.hpp"
#include "IEventListener.hpp"
#include "EventListenerHandle.hpp"

#include <memory>

class EventBus final {

public:
    static std::shared_ptr<EventBus> Create();

    ~EventBus();

    EventBus(const EventBus & other) = delete;

    template <EventDerived T, typename ...Args>
    constexpr void Raise(Args&&... args) {
        Dispatch(std::make_unique<T>(std::forward<Args>(args)...));
    }

    void Dispatch(std::unique_ptr<IEvent> event);

    [[nodiscard]] EventListenerHandle Add(std::unique_ptr<IEventListenerBase> listener);
    void Remove(EventListenerHandle && handle);

private:
    struct Impl;

public:
    EventBus(std::unique_ptr<EventBus::Impl> impl); // could not manage to make it private

private:
    std::unique_ptr<EventBus::Impl> m_pimpl;

};

