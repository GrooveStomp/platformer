#include "graphics/font.h"
#include "graphics/texture.h"
#include "math/vec2.h"
#include "world/player.h"
#include "world/gamestate.h"
#include "system/application.h"
#include "input/input.h"
#include "world/manager/input_manager.h"
#include "world/manager/player_manager.h"
#include "system/queue.h"
#include "system/queuenotifier.h"

#include <stdio.h>
#include <SDL.h>

using namespace fob::world;
using namespace fob::input;
using namespace fob::system;

int main(int argc, char *argv[])
{
    QueueState queue;
    printf("Creating ApplicationState\n");
    fob::system::ApplicationState app(480, 320);

    // -------------------------------------------------------------------------
    // Player
    // -------------------------------------------------------------------------

    printf("Creating player\n");
    PlayerState player;
    player.width = 8;
    player.height = 16;

    printf("Creating player write queue\n");
    QueueNotifierState playerWriteQueue;

    printf("Creating player read queue\n");
    QueueState playerReadQueue;
    QueueUtils::Init(&playerReadQueue);
    QueueUtils::Subscribe(&playerReadQueue, &playerWriteQueue);

    printf("Creating player manager\n");
    manager::PlayerManagerState playerManager;
    playerManager.readQueue = &playerReadQueue;
    playerManager.writeQueue = &playerWriteQueue;
    manager::PlayerManagerUtils::Add(&playerManager, &player);

    // -------------------------------------------------------------------------
    // Input
    // -------------------------------------------------------------------------

    printf("Creating input\n");
    InputState input;

    printf("Creating input write queue\n");
    QueueNotifierState inputWriteQueue;

    printf("Creating input read queue\n");
    QueueState inputReadQueue;
    QueueUtils::Init(&inputReadQueue);
    QueueUtils::Subscribe(&inputReadQueue, &inputWriteQueue);

    printf("Creating input manager\n");
    manager::InputManagerState inputManager;
    inputManager.readQueue = &inputReadQueue;
    inputManager.writeQueue = &inputWriteQueue;
    inputManager.input = &input;

    // -------------------------------------------------------------------------
    // The rest
    // -------------------------------------------------------------------------

    printf("Creating GameState\n");
    fob::world::GameState state;
    state.playerManager = &playerManager;
    state.inputManager = &inputManager;

    printf("Running ApplicationState with GameState\n");
    fob::system::ApplicationUtils::Run(app, state);

    return 0;
}
