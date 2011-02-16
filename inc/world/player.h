#ifndef FOB_WORLD_PLAYER_H
#define FOB_WORLD_PLAYER_H

namespace fob {
    namespace world {

//----------------------------------------------------------------------------
// Data definitiion for the player.
//
struct PlayerState
{
    Player(): position(0,0), rotation(0), width(1), height(1) {}
    Vec2 pos;
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
