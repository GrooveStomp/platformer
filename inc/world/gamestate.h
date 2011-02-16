#ifndef FOB_WORLD_GAMESTATE_H
#define FOB_WORLD_GAMESTATE_H

#include "inc/input/actions.h"
#include "inc/world/player.h"

namespace fob {
    namespace world {

//----------------------------------------------------------------------------
//! GameState contains all the state for the whole game.
//!
struct GameState
{
    GameState(){};
    InputActions actions;
    Player player;
}

    } // namespace world
} // namespace fob

#endif
