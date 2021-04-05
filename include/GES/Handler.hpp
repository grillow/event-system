#pragma once
#include "Bus.hpp"

#include <list>

struct Handler final {
    void Subscribe(std::shared_ptr<Event::Bus> bus,
		    std::unique_ptr<Event::IListenerBase> listener);

private:
    std::list<Event::Bus::Handle> m_handles;
};

