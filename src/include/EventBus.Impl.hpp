#pragma once
#include "EventBus.hpp"

#include <map>
#include <list>

struct EventBus::Impl {
public:
    Impl(EventBus & bus);
    
    void Dispatch(const IEvent & event);
    
    EventListenerHandle Add(std::unique_ptr<IEventListenerBase> listener);
    
    void Remove(EventListenerHandle && handle);

private:
    EventBus & m_bus;

    std::map<
        std::string,
        std::map<
            EventListenerHandle,
            std::unique_ptr<IEventListenerBase>
        >
    > m_listeners;

    uint64_t m_nlisteners;

};

