#include "EventBus.hpp"


/*
 *  EventBus::Handle
 */

EventBus::Handle::Handle(EventBus::Handle && other) :
    EventBus::Handle(other.m_bus, other.m_id) {
    other.m_bus = std::shared_ptr<EventBus>(nullptr);
}

EventBus::Handle & EventBus::Handle::operator= (EventBus::Handle && other) {
    m_bus = other.m_bus;
    m_id  = other.m_id;

    other.m_bus = std::shared_ptr<EventBus>(nullptr);

    return *this;
}

void EventBus::Handle::Release() {
    if (auto bus = m_bus.lock()) {
        bus->Remove(std::move(*this));
    }
}

bool EventBus::Handle::Active() const {
    return !m_bus.expired();
}

EventBus::Handle::~Handle() {
    Release();
    m_bus = std::shared_ptr<EventBus>(nullptr);
}

bool operator< (const EventBus::Handle & left, const EventBus::Handle & right) {
    return left.m_id < right.m_id;
}


EventBus::Handle::Handle(std::weak_ptr<EventBus> bus, const id_t id) :
        m_bus(bus),
        m_id(id)
    {}



/*
 *  EventBus::InternalHandle
 */

EventBus::InternalHandle::InternalHandle(
        const EventBus::Handle::id_t id) :
        m_id(id)
    {}

EventBus::InternalHandle::InternalHandle(
        const EventBus::Handle & handle) :
        m_id(handle.m_id)
    {}

