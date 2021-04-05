#pragma once
#include "ListenerResource.hpp"

#include <type_traits>
#include <functional>
#include <vector>
#include <map>

namespace Event {

	template <EventDerived... T>
	struct ListenerTemplate : ListenerResourceTemplate<T>... {
	    
    };


	template <EventDerived T>
	struct Listener final : ListenerTemplate<T> {
		constexpr Listener(IListenerResource::callback_t<T> callback) :
			m_callback(callback) {}

		void OnEvent(T & event) override final {
			m_callback(event);
		}

	private:
		const IListenerResource::callback_t<T> m_callback;
	};

}

