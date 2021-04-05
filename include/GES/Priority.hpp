#pragma once
#include <cstdint>

namespace Event {

    enum class Priority : int8_t {
        HOOK        =      -2,
        VERY_HIGH   =      -1,
        HIGH        =      -1,
        MEDIUM      =       0,
        LOW         =       1,
        VERY_LOW    =       1,
        POST        =       2,

        DEFAULT     =  MEDIUM
    };

}

