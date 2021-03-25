#include "EventBus.Impl.hpp"


EventBus::Impl::Impl(std::shared_ptr<EventBus> bus) : m_bus(bus), m_nlisteners(0) {}

void EventBus::Impl::Raise(std::unique_ptr<IEvent> event) {
    for (auto & listener : m_listeners[event->Type()]) {
        listener.second->Receive(*event);
    }
}

EventListenerHandle EventBus::Impl::Add(std::unique_ptr<IEventListenerBase> listener) {
    EventListenerHandle handle(std::shared_ptr<EventBus>(m_bus), m_nlisteners++);
    m_listeners[listener->Type()].emplace_back(
		    EventListenerHandleHidden(handle),
		    std::move(listener));
    return handle;
}

void EventBus::Impl::Remove(EventListenerHandle && handle) {
    for (auto & listeners : m_listeners) {
        auto it = listeners.second.begin();
        while (it != listeners.second.end()) {
            if ((*it).first.m_id == handle.m_id) {
                it = listeners.second.erase(it);
                --m_nlisteners;
            } else {
                ++it;
            }
        }
    }
}


/*
 *  EventBus
 */

std::shared_ptr<EventBus> EventBus::Create() {
    std::shared_ptr<EventBus> bus(std::make_shared<EventBus>());
    std::unique_ptr<EventBus::Impl> impl(std::make_unique<EventBus::Impl>(bus));
    bus->m_pimpl = std::move(impl);
    return bus;
}

EventBus::EventBus() : m_pimpl(nullptr) {}

EventBus::~EventBus() = default;

void EventBus::Raise(std::unique_ptr<IEvent> event) {
    m_pimpl->Raise(std::move(event));
}

EventListenerHandle EventBus::Add(std::unique_ptr<IEventListenerBase> listener) {
    return m_pimpl->Add(std::move(listener));
}

void EventBus::Remove(EventListenerHandle && handle) {
    m_pimpl->Remove(std::move(handle));
}

