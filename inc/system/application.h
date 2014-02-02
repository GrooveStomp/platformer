#ifndef FOB_SYSTEM_APPLICATION_H
#define FOB_SYSTEM_APPLICATION_H

#include "system/timer.h"

namespace fob {
    namespace world {
        struct GameState;
    }
    namespace system {

//-----------------------------------------------------------------------------
//
struct ApplicationState
{
    ApplicationState(const int iwidth = 0, const int iheight = 0):
        width(iwidth), height(iheight), running(false), skip_fe(false) {}
    int width;
    int height;
    fob::system::TimerState timer;
    bool running;
    bool skip_fe;
};

//-----------------------------------------------------------------------------
//
namespace ApplicationUtils
{
    bool Run(fob::system::ApplicationState &app, fob::world::GameState &state);
}

    } // namespace system
} // namespace fob
#endif
