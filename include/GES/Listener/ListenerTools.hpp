#pragma once
#include "ListenerBase.hpp"

namespace Event {

	template <EventDerived T>
	struct ListenerTemplate : IListenerBase {

		void Receive(IEvent & event) override final {
			OnEvent( dynamic_cast<T &>(event) );
		}

		const IEvent::Type_t & Type() const override final {
			return T::ID;
		}

        virtual void OnEvent(T & event) = 0;

    };


	template <EventDerived T>
	struct Listener final : ListenerTemplate<T> {
		using callback_t = std::function<void(T &)>;

        constexpr Listener(callback_t callback) :
			m_callback(callback) {}

		void OnEvent(T & event) override final {
			m_callback(event);
		}

	private:
		const std::function<void(T &)> m_callback;
	};

}

