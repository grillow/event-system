#pragma once
#include "../Event/EventBase.hpp"

#include <type_traits>
#include <functional>
#include <vector>
#include <map>

namespace Event {

	struct IListenerBase {
		virtual ~IListenerBase() = default;
		virtual void Receive(IEvent & event) = 0;
		virtual const std::vector<IEvent::Type_t> & Types() const = 0;
	};

	template <typename T>
	concept ListenerDerived = std::is_base_of<IListenerBase, T>::value;

}

