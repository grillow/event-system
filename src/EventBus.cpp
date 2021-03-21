#include ".EventBus.hpp"

EventBus::EventBus() : m_pimpl(std::make_unique<EventBus::Impl>()) {}

void EventBus::Dispatch(const IEvent & event) {
    m_pimpl->Dispatch(event);
}

EventListenerHandle EventBus::Add(std::unique_ptr<EventListener> listener) {
    return m_pimpl->Add(std::move(listener));
}

void EventBus::Remove(const EventListenerHandle & handle) {
    m_pimpl->Remove(handle);
}

