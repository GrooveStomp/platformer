//-----------------------------------------------------------------------------
// Author: Aaron Oman
// Contact: aaron.oman@gmail.com
// Date: Oct 19 2009
//-----------------------------------------------------------------------------
#include <sys/time.h>
#include <stddef.h>

#include "system/timer.h"

namespace fob {
    namespace system {

namespace TimerUtils {
    static const unsigned int usec_per_sec = 1000000;
    static const unsigned int usec_per_msec = 1000;

    void Init(TimerState& timer, float milliseconds)
    {
        if (milliseconds != -1) {
            timer.duration = milliseconds * usec_per_msec;
        }
        Reset(timer);
    }

    void Reset(TimerState& timer)
    {
        struct timeval time;
        gettimeofday(&time, NULL);
        timer.pauseStart = timer.start = time.tv_usec /* microseconds */ + time.tv_sec * usec_per_sec /* seconds */;
        timer.hold = 0;
    }

    bool IsExpired(const TimerState& timer)
    {
        struct timeval time;
        long long current;
        gettimeofday(&time, NULL);
        current = time.tv_usec /* microseconds */ + time.tv_sec * usec_per_sec /* seconds */;

        long long diff = (current - timer.start) - timer.hold;
        if (diff >= timer.duration) {
            return true;
        }

        return false;
    }

    float TimeElapsed(const TimerState& timer)
    {
        struct timeval time;
        long long current;
        gettimeofday(&time, NULL);
        current = time.tv_usec /* microseconds */ + time.tv_sec * usec_per_sec /* milliseconds */;

        return ((current - timer.start) - timer.hold) / usec_per_msec;
    }

    float Length(const TimerState& timer) {
        return timer.duration / usec_per_msec;
    }

    void Pause(TimerState& timer) {
        struct timeval time;
        gettimeofday(&time, NULL);
        timer.pauseStart = time.tv_usec /* microseconds */ + time.tv_sec * usec_per_sec /* milliseconds */;
    }

    void UnPause(TimerState& timer) {
        struct timeval time;
        long long pause_end;
        gettimeofday(&time, NULL);
        pause_end = time.tv_usec /* microseconds */ + time.tv_sec * usec_per_sec /* milliseconds */;
        timer.hold += (pause_end - timer.pauseStart);
        timer.pauseStart = pause_end;
    }

}

    } // namespace system
} // namespace fob
