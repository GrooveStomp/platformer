#include "system/application.h"

#include "world/gamestate.h"

#include <SDL.h>
#include <SDL/SDL_image.h>
#include <SDL_opengl.h>

namespace fob {
    namespace system {

namespace ApplicationUtils
{
    //------------------------------------------------------------------------
    // Private Helper Functions.
    //------------------------------------------------------------------------


    //------------------------------------------------------------------------
    //
    bool Init(ApplicationState &app)
    {
        /* Need to encapsulate these somehow */
        float framerate = 0.025;
        const char *title = "Platformer Demo";

        app.timer.Init(framerate);

        if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0)
        {
            printf("Unable to initialize SDL: %s\n", SDL_GetError());
            return false;
        }

        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
        SDL_Surface* screen = SDL_SetVideoMode(
            app.width,
            app.height,
            16,
            SDL_OPENGL
        );
        if (!screen)
        {
            printf(
                "Couldn't set %dx%d video mode: %s\n",
                app.width,
                app.height,
                SDL_GetError()
            );
            return false;
        }

        SDL_WM_SetCaption(title, title);
        return true;
    }


    //------------------------------------------------------------------------
    // Public class interface functions.
    //------------------------------------------------------------------------


    //------------------------------------------------------------------------
    //
    bool Run(fob::system::ApplicationState &app, fob::world::GameState &state)
    {
        if (!Init(app))
            return false;

        app.running = true;
        app.timer.Reset();

        while (app.running)
        {
            if (app.timer.Expired())
            {
                fob::world::GameStateUtils::Update(state);

                if (fob::world::GameStateUtils::ShouldExit(state)) {
                    app.running = false;
                }

                app.timer.Reset();
            }
        }

        SDL_Quit();
        return true;
    }
}

    } // namespace system
} // namespace fob
