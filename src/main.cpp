#include "graphics/font.h"
#include "graphics/texture.h"
#include "math/vec2.h"
#include "world/player.h"
#include "World/gamestate.h"
#include "system/application.h"

#include <stdio.h>
#include <SDL.h>

int main(int argc, char *argv[])
{
//    NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];

    printf("Creating ApplicationState\n");
    fob::system::ApplicationState app(320, 240);

    printf("Creating GameState\n");
    fob::world::GameState state;

    printf("Running ApplicationState with GameState\n");
    fob::system::ApplicationUtils::Run(app, state);

//    [pool release];
}
