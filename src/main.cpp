#if !defined(PLATFORM_OSX)

#include "graphics/font.h"
#include "graphics/texture.h"
#include "math/vec2.h"
#include "world/player.h"
#include "world/gamestate.h"
#include "system/application.h"

#include <stdio.h>
#include <SDL.h>

int main(int argc, char *argv[])
{

#if PLATFORM_OSX
    printf("OSX!\n");
#elif PLATFORM_LINUX
    printf("LINUX!\n");
#else
    printf("OTHER!\n");
#endif


    printf("Creating ApplicationState\n");
    fob::system::ApplicationState app(320, 240);

    printf("Creating GameState\n");
    fob::world::GameState state;

    printf("Running ApplicationState with GameState\n");
    fob::system::ApplicationUtils::Run(app, state);

    return 0;
}

#endif // !defined(PLATFORM_OSX)
