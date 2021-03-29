#include "EventListenerHandle.hpp"
#include "EventBus.hpp"
#include "EventBus.Impl.hpp"


EventListenerHandle::EventListenerHandle(EventListenerHandle && other) :
    EventListenerHandle(other.m_bus, other.m_id) {
    other.m_bus = std::shared_ptr<EventBus>(nullptr);
}

void EventListenerHandle::Release() {
    if (auto bus = m_bus.lock()) {
        bus->Remove(std::move(*this));
    }
}

bool EventListenerHandle::Active() const {
    return !m_bus.expired();
}

EventListenerHandle::~EventListenerHandle() {
    Release();
    m_bus = std::shared_ptr<EventBus>(nullptr);
}

bool operator< (const EventListenerHandle & left,
                const EventListenerHandle & right) {
    return left.m_id < right.m_id;
}


EventListenerHandle::EventListenerHandle(std::weak_ptr<EventBus> bus, const id_t id) :
        m_bus(bus),
        m_id(id)
    {}



/*
 *  Hidden
 */

EventBus::Impl::EventListenerHandleHidden::EventListenerHandleHidden(const EventListenerHandle::id_t id) :
        m_id(id)
    {}

EventBus::Impl::EventListenerHandleHidden::EventListenerHandleHidden(const EventListenerHandle & handle) :
        m_id(handle.m_id)
    {}

