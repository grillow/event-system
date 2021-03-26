#include "EventBus.Impl.hpp"


EventBus::Impl::Impl() : m_bus(std::shared_ptr<EventBus>(nullptr)), m_nlisteners(0) {}


void EventBus::Impl::Raise(std::unique_ptr<IEvent> event) {
    for (auto & listener : m_listeners_type[event->Type()]) {
        if (auto shared = listener.lock()) {
            shared->Receive(*event);
        } else {
            ///TODO: handle this nonsense
        }
    }
}


EventListenerHandle EventBus::Impl::Add(std::unique_ptr<IEventListenerBase> listener) {
    const EventListenerHandleHidden handle(m_nlisteners++);
    m_listeners_handle[handle] = std::move(listener);
    auto ref = m_listeners_handle[handle];
    for (auto type : ref->Types()) {
        m_listeners_type[type].emplace_back(ref);
    }
    return EventListenerHandle(std::shared_ptr<EventBus>(m_bus), handle.m_id);
}


void EventBus::Impl::Remove(EventListenerHandle && handle) {
    EventListenerHandleHidden hidden(handle);

    std::shared_ptr<IEventListenerBase> ref =
        std::shared_ptr<IEventListenerBase>(m_listeners_handle[hidden]);

    for (auto & listeners : m_listeners_type) {
        auto it = listeners.second.begin();
        while (it != listeners.second.end()) {
            if (std::shared_ptr<IEventListenerBase>(*it) == ref) {
                it = listeners.second.erase(it);
                --m_nlisteners;
            } else {
                ++it;
            }
        }
    }
    
    m_listeners_handle.erase(hidden);

}



/*
 *  EventBus
 */

std::shared_ptr<EventBus> EventBus::Create() {
    std::shared_ptr<EventBus> bus(
            std::make_shared<EventBus>(
                std::make_unique<EventBus::Impl>()));
    bus->m_pimpl->m_bus = bus;

    return bus;
}


EventBus::EventBus(std::unique_ptr<EventBus::Impl> impl) : m_pimpl(std::move(impl)) {}


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

