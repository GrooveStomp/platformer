#ifndef FOB_WORLD_GAMESTATE_H
#define FOB_WORLD_GAMESTATE_H

#include "input/input.h"
#include "world/player.h"

namespace fob {
    namespace world {

//----------------------------------------------------------------------------
//! GameState contains all the state for the whole game.
//!
struct GameState
{
    GameState() {};
    fob::input::InputState actions;
    fob::world::PlayerState player;
};

    } // namespace world
} // namespace fob

#endif
