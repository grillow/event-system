#pragma once

namespace Event {

    enum class Priority : int8_t {
        HOOK     =     -2,
        HIGH     =     -1,
        MEDIUM   =      0,
        LOW      =      1,

        DEFAULT  = MEDIUM
    };

}

