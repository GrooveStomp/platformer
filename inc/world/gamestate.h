#ifndef FOB_WORLD_GAMESTATE_H
#define FOB_WORLD_GAMESTATE_H

namespace fob {

    namespace system {
        struct QueueState;
        struct QueueNotifierState;
    }

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

    fob::system::QueueState* messageQueue;
    fob::system::QueueNotifierState* messageNotifier;
};

namespace GameStateUtils
{
    void Update(GameState* const state);
    void Draw(const GameState* const state);
    bool ShouldExit(const GameState* const state);
}

    } // namespace world
} // namespace fob

#endif // FOB_WORLD_GAMESTATE_H
