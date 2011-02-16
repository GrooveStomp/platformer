//-----------------------------------------------------------------------------
// Author: Aaron Oman
// Contact: aaron.oman@gmail.com
// Date: Oct 19 2009
//-----------------------------------------------------------------------------

#include "system/timer.h"
#include "stdio.h"

namespace fob {
    namespace system {

        Timer::Timer(float milliseconds) :
            _pause_start(0),
            _hold(0)
        {
            struct timeval time;
            _duration = milliseconds * usec_per_msec;

            gettimeofday(&time, NULL);
            _start = time.tv_usec /* microseconds */ + time.tv_sec * usec_per_sec /* seconds */;
        }

        void Timer::Reset() {
            struct timeval time;
            gettimeofday(&time, NULL);
            _pause_start = _start = time.tv_usec /* microseconds */ + time.tv_sec * usec_per_sec /* seconds */;
            _hold = 0;
        }

        void Timer::Init(float milliseconds) {
            if (milliseconds != -1) {
                _duration = milliseconds * usec_per_msec;
            }
            Reset();
        }

        void Timer::Pause() {
            struct timeval time;
            gettimeofday(&time, NULL);
            _pause_start = time.tv_usec /* microseconds */ + time.tv_sec * usec_per_sec /* milliseconds */;
        }

        void Timer::UnPause() {
            struct timeval time;
            int64_t pause_end;
            gettimeofday(&time, NULL);
            pause_end = time.tv_usec /* microseconds */ + time.tv_sec * usec_per_sec /* milliseconds */;
            _hold += (pause_end - _pause_start);
            _pause_start = pause_end;
        }

        bool Timer::Expired() {
            struct timeval time;
            int64_t current;
            gettimeofday(&time, NULL);
            current = time.tv_usec /* microseconds */ + time.tv_sec * usec_per_sec /* seconds */;

            int64_t diff = (current - _start) - _hold;
            if (diff >= _duration) {
                return true;
            }

            return false;
        }

        float Timer::Elapsed() {
            struct timeval time;
            int64_t current;
            gettimeofday(&time, NULL);
            current = time.tv_usec /* microseconds */ + time.tv_sec * usec_per_sec /* milliseconds */;

            return ((current - _start) - _hold) / usec_per_msec;
        }

        float Timer::Length() {
            return _duration / usec_per_msec;
        }

    } // namespace system
} // namespace fob
