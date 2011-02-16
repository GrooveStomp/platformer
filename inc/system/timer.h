//-----------------------------------------------------------------------------
// Author: Aaron Oman
// Contact: aaron.oman@gmail.com
// Date: Oct 19 2009
//-----------------------------------------------------------------------------

#ifndef TIMER_H
#define TIMER_H

#include <sys/time.h>
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

namespace fob {
    namespace system {

        static const unsigned usec_per_sec = 1000000;
        static const unsigned usec_per_msec = 1000;

        class Timer {
            public:
                Timer(float milliseconds=0);
                void Init(float milliseconds=-1);
                void Reset();
                bool Expired();
                float Elapsed(); // milliseconds
                float Length();
                void Pause();
                void UnPause();

                int64_t _start;
                int64_t _pause_start;
                int64_t _hold;
                float _duration;
        };

    } // system
} // fob

#endif
