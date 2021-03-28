#pragma once
#include "EventBus.hpp"
#include "UniqueGenerator.hpp"

#include <map>
#include <list>
#include <utility>


struct EventBus::Impl {
friend struct EventBus;
public:
    Impl();
    
    void Raise(std::unique_ptr<IEvent> event);
    
    EventListenerHandle Add(std::unique_ptr<IEventListenerBase> listener);
    
    void Remove(EventListenerHandle && handle);

private:
    struct EventListenerHandleHidden;

    std::weak_ptr<EventBus> m_bus;
    
    std::map<
        EventListenerHandleHidden,
        std::shared_ptr<IEventListenerBase>
    > m_listeners_handle;
    
    std::map<
        IEvent::Type_t,
        std::list<
            std::weak_ptr<IEventListenerBase> 
        >
    > m_listeners_type;

private:
    UniqueGenerator m_generator;

};


struct EventBus::Impl::EventListenerHandleHidden final {
    explicit EventListenerHandleHidden(const uint64_t id);
    explicit EventListenerHandleHidden(const EventListenerHandle & handle);

public:
    const uint64_t m_id;

public:
    friend constexpr bool operator< (const EventListenerHandleHidden & left,
            const EventListenerHandleHidden & right) {
        return left.m_id < right.m_id;
    }

    friend constexpr bool operator==(const EventListenerHandleHidden & left,
            const EventListenerHandleHidden & right) {
        return left.m_id == right.m_id;
    }
};

