#pragma once
#include "Bus.hpp"

#include <list>

namespace Event {

    struct Handler final {
        void Subscribe(std::shared_ptr<Event::Bus> bus,
                std::unique_ptr<Event::IListenerBase> listener) {
            m_handles.emplace_back(bus->Add(std::move(listener)));
        }

    private:
        std::list<Event::Bus::Handle> m_handles;
    };

}

