#include "EventBus.hpp"


std::shared_ptr<EventBus> EventBus::Create() {
    auto bus = std::make_shared<EventBus>(std::shared_ptr<EventBus>(nullptr));
    bus->m_bus = bus;
    return bus;
}


EventBus::EventBus(std::weak_ptr<EventBus> bus) : m_bus(bus) {}


void EventBus::Raise(std::unique_ptr<IEvent> event) {
    for (auto & priority_map : m_listeners) {
        for (auto & listener : priority_map.second[event->Type()]) {
            listener.lock()->Receive(*event);
        }
    }
}


EventBus::Handle EventBus::Add(std::unique_ptr<IEventListenerBase> listener,
		Priority priority) {
    const Handle::id_t unique_id = m_generator.Get();

    const InternalHandle handle(unique_id);
    m_listeners_handle[handle] = std::move(listener);
    auto ref = m_listeners_handle[handle];
    for (auto type : ref->Types()) {
        m_listeners[priority][type].emplace_back(ref);
    }
    return Handle(m_bus, handle.m_id);
}


void EventBus::Remove(EventBus::Handle && handle) {
    const Handle::id_t unique_id = handle.m_id;
    m_generator.Release(unique_id);

    InternalHandle hidden(handle);

    std::shared_ptr<IEventListenerBase> ref =
        std::shared_ptr<IEventListenerBase>(m_listeners_handle[hidden]);

    ///TODO: optimize
    for (auto & priority_map : m_listeners) {
        for (auto & listeners : priority_map.second) {
            auto it = listeners.second.begin();
            while (it != listeners.second.end()) {
                if (std::shared_ptr<IEventListenerBase>(*it) == ref) {
                    it = listeners.second.erase(it);
                } else {
                    ++it;
                }
            }
        }

    }
    
    m_listeners_handle.erase(hidden);

}

