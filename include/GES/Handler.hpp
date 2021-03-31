#pragma once
#include "EventBus.hpp"

#include <list>

struct Handler final {
    void Subscribe(std::shared_ptr<EventBus> bus,
		    std::unique_ptr<IEventListenerBase> listener);

private:
    std::list<EventBus::Handle> m_handles;
};

