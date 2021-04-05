#pragma once
#include "ListenerBase.hpp"

#include <map>

namespace Event {

	struct IListenerResource : IListenerBase {
		template <EventDerived TEvent = IEvent>
		using callback_t = std::function<void(TEvent &)>;

		void Receive(IEvent & event) override final {
			m_callbacks[event.Type()](event);
		}
		
		const std::vector<IEvent::Type_t> & Types() const override final {
			return m_types;
		}

	protected:
		std::vector<IEvent::Type_t> m_types;
		std::map<IEvent::Type_t, callback_t<>> m_callbacks;
	};


	template <EventDerived T>
	struct ListenerResourceTemplate : virtual IListenerResource {
		constexpr ListenerResourceTemplate() {
			m_types.emplace_back(T::ID);
			m_callbacks[T::ID] = [this](IEvent & event){ OnEvent(dynamic_cast<T &>(event)); };
		}
		virtual void OnEvent(T & event) = 0;
	};

}

