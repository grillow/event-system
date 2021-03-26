#include "Subscriber.hpp"

void Subscriber::Subscribe(std::shared_ptr<EventBus> bus,
		std::unique_ptr<IEventListenerBase> listener) {
    m_handles.emplace_back(bus->Add(std::move(listener)));
}
