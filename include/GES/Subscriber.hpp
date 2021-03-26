#include "EventListenerHandle.hpp"
#include "EventBus.hpp"

#include <list>

struct Subscriber {
protected:
    void Subscribe(std::shared_ptr<EventBus> bus,
		    std::unique_ptr<IEventListenerBase> listener);

private:
    std::list<EventListenerHandle> m_handles;
};

