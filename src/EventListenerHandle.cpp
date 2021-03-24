#include "EventListenerHandle.hpp"
#include "EventBus.hpp"
#include "EventBus.Impl.hpp"


EventListenerHandle::EventListenerHandle(EventListenerHandle && other) :
    EventListenerHandle(other.m_bus, other.m_id) {
    other.m_destroyed = true;
}

EventListenerHandle::~EventListenerHandle() {
    if (!m_destroyed) {
	if (auto bus = m_bus.lock()) {
	    bus->Remove(std::move(*this));
	} else { // anti-idiot
	    ///TODO: handle this error
	}
    }
}


bool operator< (const EventListenerHandle & left,
                const EventListenerHandle & right) {
    return left.m_id < right.m_id;
}


EventListenerHandle::EventListenerHandle(std::weak_ptr<EventBus> bus, const uint64_t id) :
        m_bus(bus),
        m_id(id),
        m_destroyed(false)
    {}


EventBus::Impl::EventListenerHandleHidden::EventListenerHandleHidden(const EventListenerHandle & handle) :
        m_id(handle.m_id)
    {}

