#include "Handler.hpp"

using namespace Event;

void Handler::Subscribe(std::shared_ptr<Event::Bus> bus,
		std::unique_ptr<Event::IListenerBase> listener) {
    m_handles.emplace_back(bus->Add(std::move(listener)));
}

