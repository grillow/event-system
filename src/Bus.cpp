#include "Bus.hpp"

using namespace Event;

std::shared_ptr<Bus> Bus::Create() {
    auto bus = std::make_shared<Bus>(std::shared_ptr<Bus>(nullptr));
    bus->m_bus = bus;
    return bus;
}


Bus::Bus(std::weak_ptr<Bus> bus) : m_bus(bus) {}


void Bus::Raise(std::unique_ptr<IEvent> event) {
    for (auto & priority_map : m_listeners) {
        for (auto & listener : priority_map.second[event->Type()]) {
            listener.lock()->Receive(*event);
        }
    }
}


Bus::Handle Bus::Add(std::unique_ptr<IListenerBase> listener,
		Priority priority) {
    const Handle::id_t unique_id = m_generator.Get();

    const InternalHandle handle(unique_id);
    m_listeners_handle[handle] = std::move(listener);
    auto ref = m_listeners_handle[handle];
        m_listeners[priority][ref->Type()].emplace_back(ref);
    return Handle(m_bus, handle.m_id);
}


void Bus::Remove(Bus::Handle && handle) {
    const Handle::id_t unique_id = handle.m_id;
    m_generator.Release(unique_id);

    InternalHandle hidden(handle);

    std::shared_ptr<IListenerBase> ref =
        std::shared_ptr<IListenerBase>(m_listeners_handle[hidden]);

    ///TODO: optimize
    for (auto & priority_map : m_listeners) {
        for (auto & listeners : priority_map.second) {
            auto it = listeners.second.begin();
            while (it != listeners.second.end()) {
                if (std::shared_ptr<IListenerBase>(*it) == ref) {
                    it = listeners.second.erase(it);
                } else {
                    ++it;
                }
            }
        }

    }
    
    m_listeners_handle.erase(hidden);

}

