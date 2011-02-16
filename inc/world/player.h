#ifndef FOB_WORLD_PLAYER_H
#define FOB_WORLD_PLAYER_H

#include "math/vec2.h"

namespace fob {
    namespace world {
        struct GameState;

//----------------------------------------------------------------------------
// Data definitiion for the player.
//
struct PlayerState
{
    PlayerState(): position(0,0), rotation(0), width(1), height(1) {}
    fob::math::Vec2 position;
    float rotation;
    float width;
    float height;
};

//----------------------------------------------------------------------------
// Public utility functions that operate on player state.
//
namespace PlayerUtils
{
    void Update(float dt, GameState &state);
}

    } // namespace world
} // namespace fob

#endif
