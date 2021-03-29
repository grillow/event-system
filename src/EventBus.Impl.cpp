#include "EventBus.Impl.hpp"


/*
 *  EventBus::Impl
 */

EventBus::Impl::Impl() : m_bus(std::shared_ptr<EventBus>(nullptr)) {}


void EventBus::Impl::Raise(std::unique_ptr<IEvent> event) {
    for (auto & listener : m_listeners_type[event->Type()]) {
        auto shared = listener.lock();
        shared->Receive(*event);
    }
}


EventBus::Handle EventBus::Impl::Add(std::unique_ptr<IEventListenerBase> listener) {
    const EventBus::Handle::id_t unique_id = m_generator.Get();
    
    const Handle handle(unique_id);
    m_listeners_handle[handle] = std::move(listener);
    auto ref = m_listeners_handle[handle];
    for (auto type : ref->Types()) {
        m_listeners_type[type].emplace_back(ref);
    }
    return EventBus::Handle(std::shared_ptr<EventBus>(m_bus), handle.m_id);
}


void EventBus::Impl::Remove(EventBus::Handle && handle) {
    const EventBus::Handle::id_t unique_id = handle.m_id;
    m_generator.Release(unique_id);

    Handle hidden(handle);

    std::shared_ptr<IEventListenerBase> ref =
        std::shared_ptr<IEventListenerBase>(m_listeners_handle[hidden]);

    for (auto & listeners : m_listeners_type) {
        auto it = listeners.second.begin();
        while (it != listeners.second.end()) {
            if (std::shared_ptr<IEventListenerBase>(*it) == ref) {
                it = listeners.second.erase(it);
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
    std::shared_ptr<EventBus> bus =
        std::make_shared<EventBus>(std::make_unique<EventBus::Impl>());
    bus->m_pimpl->m_bus = bus;

    return bus;
}


EventBus::EventBus(std::unique_ptr<EventBus::Impl> impl) : m_pimpl(std::move(impl)) {}


EventBus::~EventBus() = default;


void EventBus::Raise(std::unique_ptr<IEvent> event) {
    m_pimpl->Raise(std::move(event));
}


EventBus::Handle EventBus::Add(std::unique_ptr<IEventListenerBase> listener) {
    return m_pimpl->Add(std::move(listener));
}


void EventBus::Remove(EventBus::Handle && handle) {
    m_pimpl->Remove(std::move(handle));
}

