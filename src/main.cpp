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
    // -------------------------------------------------------------------------
    // Configure Messaging Systems
    // -------------------------------------------------------------------------

    QueueNotifierState appMessages;
    QueueNotifierUtils::Name(&appMessages, "Application Messages");

    QueueNotifierState playerMessages;
    QueueNotifierUtils::Name(&playerMessages, "Player Messages");

    QueueNotifierState inputMessages;
    QueueNotifierUtils::Name(&inputMessages, "Input Messages");

    QueueState playerQueue;
    QueueUtils::Name(&playerQueue, "Player Read Message Queue");
    QueueUtils::Init(&playerQueue);

    QueueState inputQueue;
    QueueUtils::Name(&inputQueue, "Input Read Message Queue");
    QueueUtils::Init(&inputQueue);

    QueueState appQueue;
    QueueUtils::Name(&appQueue, "Application Read Message Queue");
    QueueUtils::Init(&appQueue);

    QueueNotifierUtils::Subscribe(&appMessages, &playerQueue);
    QueueNotifierUtils::Subscribe(&appMessages, &inputQueue);

    QueueNotifierUtils::Subscribe(&inputMessages, &playerQueue);
    QueueNotifierUtils::Subscribe(&inputMessages, &appQueue);

    // -------------------------------------------------------------------------
    // Application
    // -------------------------------------------------------------------------

    printf("Creating ApplicationState\n");
    fob::system::ApplicationState app(480, 320);

    // -------------------------------------------------------------------------
    // Player
    // -------------------------------------------------------------------------

    printf("Creating player\n");
    PlayerState player;
    player.width = 8;
    player.height = 16;

    printf("Creating player manager\n");
    manager::PlayerManagerState playerManager;
    playerManager.messageQueue = &playerQueue;
    playerManager.messageNotifier = &playerMessages;
    manager::PlayerManagerUtils::Add(&playerManager, &player);

    // -------------------------------------------------------------------------
    // Input
    // -------------------------------------------------------------------------

    printf("Creating input\n");
    InputState input;

    printf("Creating input manager\n");
    manager::InputManagerState inputManager;
    inputManager.messageQueue = &inputQueue;
    inputManager.messageNotifier = &inputMessages;
    inputManager.input = &input;

    // -------------------------------------------------------------------------
    // The rest
    // -------------------------------------------------------------------------

    printf("Creating GameState\n");
    fob::world::GameState state;
    state.playerManager = &playerManager;
    state.inputManager = &inputManager;
    state.messageQueue = &appQueue;
    state.messageNotifier = &appMessages;

    printf("Running ApplicationState with GameState\n");
    fob::system::ApplicationUtils::Run(&app, &state);

    return 0;
}
