#ifndef FOB_WORLD_GAMESTATE_H
#define FOB_WORLD_GAMESTATE_H

#include "system/types.h"
#include "input/input.h"
#include "world/player.h"

namespace fob {
    namespace world {

      namespace manager {
        struct InputManagerState;
        struct PlayerManagerState;
      }

struct GameState
{
    GameState() {};
    fob::world::manager::PlayerManagerState* playerManager;
    fob::world::manager::InputManagerState* inputManager;
};

namespace GameStateUtils
{
    void Update(GameState &state);
    void Draw(const GameState &state);
    bool ShouldExit(const GameState &state);
}

    } // namespace world
} // namespace fob

#endif // FOB_WORLD_GAMESTATE_H
