#include <memory>
#include "EventBus.hpp"

/*
 *  EventBus::InternalHandle
 */

struct EventBus::InternalHandle final {
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

