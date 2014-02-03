#include "graphics/font.h"
#include "graphics/texture.h"
#include "math/vec2.h"
#include "world/player.h"
#include "world/gamestate.h"
#include "system/application.h"
#include "input/input.h"
#include "world/manager/input_manager.h"
#include "world/manager/player_manager.h"

#include <stdio.h>
#include <SDL.h>

using namespace fob::world;
using namespace fob::input;

int main(int argc, char *argv[])
{
    printf("Creating ApplicationState\n");
    fob::system::ApplicationState app(480, 320);

    printf("Creating player\n");
    PlayerState player;
    player.width = 8;
    player.height = 16;

    printf("Creating player manager\n");
    manager::PlayerManagerState playerManager;
    manager::PlayerManagerUtils::Add(playerManager, player);

    printf("Creating input\n");
    InputState input;

    printf("Creating input manager\n");
    manager::InputManagerState inputManager;
    inputManager.input = &input;

    printf("Creating GameState\n");
    fob::world::GameState state;
    state.playerManager = &playerManager;
    state.inputManager = &inputManager;

    printf("Running ApplicationState with GameState\n");
    fob::system::ApplicationUtils::Run(app, state);

    return 0;
}
