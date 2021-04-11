#pragma once
#include "../Event/EventBase.hpp"

#include <type_traits>
#include <vector>

namespace Event {

	struct IListenerBase {
		virtual ~IListenerBase() = default;
		virtual void Receive(IEvent & event) = 0;
		virtual const IEvent::Type_t & Type() const = 0;
	};

	template <typename T>
	concept ListenerDerived = std::is_base_of<IListenerBase, T>::value;

}

