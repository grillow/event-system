#include "EventBus.Impl.hpp"

EventBus::Impl::Impl() : m_nlisteners(0) {}

void EventBus::Impl::Dispatch(const IEvent & event) {
    for (const auto & listener : m_listeners[event.Type()]) {
        listener.Dispatch(event);
    }
}

EventBus::Impl::Add(std::unique_ptr<EventListener> listener) {
    return EventListenerHandle(*this, m_nlisteners++);
}

void EventBus::Impl::Remove(const EventListenerHandle & handle) {
    for (const auto & listeners : m_listeners) {
        auto it = listeners.find(handle);
        if (it != listeners.end()) {
            listeners.erase(it);
            --m_nlisteners;
        }
    }
}

