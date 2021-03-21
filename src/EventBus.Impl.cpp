#include "EventBus.Impl.hpp"
#include <iostream>
EventBus::Impl::Impl(EventBus & bus) : m_bus(bus), m_nlisteners(0) {}

void EventBus::Impl::Dispatch(const IEvent & event) {
    for (auto & listener : m_listeners[event.Type()]) {
        listener.second->Dispatch(event);
    }
}

EventListenerHandle EventBus::Impl::Add(std::unique_ptr<IEventListenerBase> listener) {
    EventListenerHandle handle(m_bus, m_nlisteners++);
    m_listeners[listener->Type()][handle] = std::move(listener);
    return handle;
}

void EventBus::Impl::Remove(EventListenerHandle && handle) {
    std::cout << "b\n";
    for (auto & listeners : m_listeners) {
        auto it = listeners.second.find(handle);
        if (it != listeners.second.end()) {
            listeners.second.erase(it);
            --m_nlisteners;
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

