#ifndef FOB_WORLD_MANAGER_PLAYER_MANAGER_H
#define FOB_WORLD_MANAGER_PLAYER_MANAGER_H

#include "system/types.h"

namespace fob {

    namespace system {
        struct QueueState;
        struct QueueNotifierState;
    }

    namespace world {
        struct PlayerState;

        namespace manager {

struct PlayerManagerState
{
    PlayerManagerState(): playerCount(0) {}
    PlayerState* players[QUEUE_SIZE];
    unsigned char playerUuids[QUEUE_SIZE][UUID_SIZE];
    fob::system::QueueState* messageQueue;
    fob::system::QueueNotifierState* messageNotifier;
    unsigned int playerCount;
};

namespace PlayerManagerUtils
{
    void Add(PlayerManagerState* const manager, PlayerState* const player);
    void Update(PlayerManagerState* const manager);
}

        } // namespace manager
    } // namespace world
} // namespace fob

#endif // FOB_WORLD_MANAGER_PLAYER_MANAGER_H
