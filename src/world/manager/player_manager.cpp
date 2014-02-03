#include "world/manager/player_manager.h"
#include "world/player.h"
#include "system/queue.h"
#include "system/queuenotifier.h"

#include <string.h>

namespace fob {
    namespace world {
        namespace manager {

namespace PlayerManagerUtils
{
    void Add(PlayerManagerState* const manager, PlayerState* const player)
    {
        if (UCHAR_MAX == manager->playerCount) {
            return;
        }

        strncpy((char *)(manager->playerUuids[manager->playerCount]), (char *)(player->uuid), UUID_SIZE);
        manager->players[manager->playerCount] = player;
        manager->playerCount++;
    }

    void Update(PlayerManagerState* const manager)
    {
        using namespace fob::system;

        for (unsigned int i=0; i < manager->playerCount; i++)
        {
            PlayerUtils::Update(manager->players[i], manager->readQueue, manager->writeQueue);
        }
        QueueUtils::Clear(manager->readQueue);
    }
}

        } // namespace manager
    } // namespace world
} // namespace fob
