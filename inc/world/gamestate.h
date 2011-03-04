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
    fob::input::InputState input;
    fob::world::PlayerState player;
};

//-----------------------------------------------------------------------------
//
namespace GameStateUtils
{
    void Update(GameState &state);
    void Draw(const GameState &state);
    bool ShouldExit(const GameState &state);
}

    } // namespace world
} // namespace fob

#endif
