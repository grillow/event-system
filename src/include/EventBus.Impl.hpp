#pragma once
#include "EventBus.hpp"

#include <map>
#include <unordered_map>
#include <list>

struct EventBus::Impl {
public:
    Impl();
    
    void Dispatch(const IEvent & event);
    
    EventListenerHandle Add(std::unique_ptr<IEventListener> listener);
    
    void Remove(const EventListenerHandle & handle);

private:
    std::map<
        std::string,
        std::unordered_map<
            const EventListenerHandle,
            std::unique_ptr<IEventListener>
        >
    > m_listeners;

    uint64_t m_nlisteners;

};

