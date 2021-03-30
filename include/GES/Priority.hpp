#pragma once
#include <array>

///TODO: flexibility
namespace Priority {
    using Priority_t = int8_t;
    enum class DefaultPrioritySystem : Priority_t {
        HOOK     =     -2,
        HIGH     =     -1,
        MEDIUM   =      0,
        LOW      =      1,

        DEFAULT  = MEDIUM
    };

    /*
    static constexpr auto Priorities = std::to_array<DefaultPrioritySystem>({
            DefaultPrioritySystem::HOOK,
            DefaultPrioritySystem::HIGH,
            DefaultPrioritySystem::MEDIUM,
            DefaultPrioritySystem::LOW
        });
    */
}

