//-----------------------------------------------------------------------------
// Author: Aaron Oman
// Contact: aaron.oman@gmail.com
// Date: Oct 19 2009
//-----------------------------------------------------------------------------

#ifndef TIMER_H
#define TIMER_H

namespace fob {
    namespace system {

struct TimerState
{
    TimerState(): start(0), pauseStart(0), hold(0), duration(0) {}
    long long start;
    long long pauseStart;
    long long hold;
    float duration;
};

namespace TimerUtils
{
    void Init(TimerState& timer, float milliseconds = -1);
    void Reset(TimerState& timer);
    bool IsExpired(const TimerState& timer);
    float TimeElapsed(const TimerState &timer);
    float Length(const TimerState &timer);
    void Pause(TimerState &timer);
    void UnPause(TimerState &timer);
}

    } // system
} // fob

#endif
