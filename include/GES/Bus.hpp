#pragma once
#include "IEvent.hpp"
#include "Utils/UniqueGenerator.hpp"
#include "IEventListener.hpp"
#include "Priority.hpp"

#include <initializer_list>
#include <memory>
#include <array>
#include <list>
#include <map>

namespace Event {

    class Bus final {
    public:
        /*
         *  Bus::Handle
         */

        struct Handle final {
            friend class Bus;

            using id_t = uint64_t;

            Handle(const Handle & other) = delete;
            Handle(Handle && other);
            Handle & operator= (Handle && other);
            ~Handle();

            void Release();
            bool Active() const;

            friend bool operator< (const Handle & left, const Handle & right) {
                return left.m_id < right.m_id;
            }

        private:
            Handle(std::weak_ptr<Bus> bus, const id_t id);

            std::weak_ptr<Bus> m_bus;
            id_t m_id;
        };

    public:
        static std::shared_ptr<Bus> Create();

        Bus(std::weak_ptr<Bus> bus);    ///TODO: make it private
        Bus(const Bus & other) = delete;

        // Raise Event
        template <EventDerived T, typename ...Args>
        constexpr void Raise(Args&&... args) {
            Raise(std::make_unique<T>(std::forward<Args>(args)...));
        }
        void Raise(std::unique_ptr<IEvent> event);

        // Add Event Listener
        template <ListenerDerived T, typename ...Args>
        [[nodiscard]] constexpr Handle Add(Args&&... args) {
            return Add<T>(Priority::DEFAULT, std::forward<Args>(args)...);
        }
        template <ListenerDerived T, typename ...Args>
        [[nodiscard]] constexpr Handle Add(Priority priority, Args&&... args) {
            return Add(std::make_unique<T>(std::forward<Args>(args)...), priority);
        }
        [[nodiscard]] Handle Add(std::unique_ptr<IListenerBase> listener,
                Priority priority = Priority::DEFAULT);
        
        // Remove Event Listener
        void Remove(Handle && handle);

    private:
        std::weak_ptr<Bus> m_bus;
        struct InternalHandle;

            
        std::map<
            InternalHandle,
            std::shared_ptr<IListenerBase>
        > m_listeners_handle;
       
        std::map<Priority,
            std::map<
                IEvent::Type_t,
                std::list<
                    std::weak_ptr<IListenerBase> 
                >
            >
        > m_listeners;

        UniqueGenerator<Bus::Handle::id_t> m_generator;
    };


    /*
     *  Bus::InternalHandle
     */

    struct Bus::InternalHandle final {
        explicit InternalHandle(const Handle::id_t id);
        explicit InternalHandle(const Handle & handle);

        const Handle::id_t m_id;

        friend constexpr bool operator< (const InternalHandle & left,
                const InternalHandle & right) {
            return left.m_id < right.m_id;
        }

        friend constexpr bool operator==(const InternalHandle & left,
                const InternalHandle & right) {
            return left.m_id == right.m_id;
        }
    };

}

