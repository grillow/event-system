#pragma once
#include "EventBus.hpp"

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

    struct cmp {
        constexpr bool operator()(const auto & left,
                const auto & right) const {
            return left.m_id < right.m_id;
        }
    };
    
    std::map<
        EventListenerHandleHidden,
        std::shared_ptr<IEventListenerBase>,
        cmp
    > m_listeners_handle;
    
    std::map<
        std::string,
        std::list<
            std::weak_ptr<IEventListenerBase> 
        >
    > m_listeners_type;

    uint64_t m_nlisteners;

};


struct EventBus::Impl::EventListenerHandleHidden final {
    EventListenerHandleHidden(const uint64_t id);
    EventListenerHandleHidden(const EventListenerHandle & handle);
    const uint64_t m_id;

    friend constexpr bool operator==(const EventListenerHandleHidden & left,
            const EventListenerHandleHidden & right) {
        return left.m_id == right.m_id;
    }
};

