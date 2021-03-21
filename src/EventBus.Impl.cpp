#include "EventBus.Impl.hpp"


EventBus::Impl::Impl(EventBus & bus) : m_bus(bus), m_nlisteners(0) {}

void EventBus::Impl::Dispatch(const IEvent & event) {
    for (auto & listener : m_listeners[event.Type()]) {
        listener.second->Dispatch(event);
    }
}

EventListenerHandle EventBus::Impl::Add(std::unique_ptr<IEventListenerBase> listener) {
    EventListenerHandle handle(m_bus, m_nlisteners++);
    m_listeners[listener->Type()].emplace_back(EventListenerHandleHidden(handle), std::move(listener));
    return handle;
}

void EventBus::Impl::Remove(EventListenerHandle && handle) {
    for (auto & listeners : m_listeners) {
        auto it = listeners.second.begin();
        while (it != listeners.second.end()) {
            if ((*it).first.m_id == handle.m_id) {
                it = listeners.second.erase(it);
            } else {
                ++it;
            }
        }
    }
}


/*
 *  EventBus
 */


EventBus::EventBus() : m_pimpl(std::make_unique<EventBus::Impl>(*this)) {}

EventBus::~EventBus() = default;

void EventBus::Dispatch(const IEvent & event) {
    m_pimpl->Dispatch(event);
}

EventListenerHandle EventBus::Add(std::unique_ptr<IEventListenerBase> listener) {
    return m_pimpl->Add(std::move(listener));
}

void EventBus::Remove(EventListenerHandle && handle) {
    m_pimpl->Remove(std::move(handle));
}

