#pragma once
#include "EventBus.hpp"

#include <map>
#include <list>
#include <utility>

struct EventBus::Impl {
public:
    Impl(EventBus & bus);
    
    void Dispatch(IEvent & event);
    
    EventListenerHandle Add(std::unique_ptr<IEventListenerBase> listener);
    
    void Remove(EventListenerHandle && handle);

private:
    struct EventListenerHandleHidden;

    EventBus & m_bus;

    std::map<
        std::string,
        std::list<
            std::pair<
                EventListenerHandleHidden,
                std::unique_ptr<IEventListenerBase>
            >
        >
    > m_listeners;

    uint64_t m_nlisteners;

};


struct EventBus::Impl::EventListenerHandleHidden final {
    EventListenerHandleHidden(const EventListenerHandle & handle);
    const uint64_t m_id;
};

