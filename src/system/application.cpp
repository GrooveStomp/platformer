#include "system/application.h"
#include "world/gamestate.h"

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_opengl.h>

namespace fob {
    namespace system {

namespace ApplicationUtils {

    bool Init(ApplicationState* const app)
    {
        /* Need to encapsulate these somehow */
        float framerate = 0.025;
        const char *title = "Platformer Demo";

        TimerUtils::Init(app->timer, framerate);

        if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0)
        {
            printf("Unable to initialize SDL: %s\n", SDL_GetError());
            return false;
        }

        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
        SDL_Surface* screen = SDL_SetVideoMode(
            app->width,
            app->height,
            16,
            SDL_OPENGL
        );
        if (!screen)
        {
            printf(
                "Couldn't set %dx%d video mode: %s\n",
                app->width,
                app->height,
                SDL_GetError()
            );
            return false;
        }

        SDL_WM_SetCaption(title, title);
        return true;
    }

    bool Run(fob::system::ApplicationState* const app, fob::world::GameState* const state)
    {
        using namespace fob::world;

        if (!Init(app))
            return false;

        app->running = true;
        TimerUtils::Reset(app->timer);

        while (app->running)
        {
            if (TimerUtils::IsExpired(app->timer))
            {
                GameStateUtils::Update(state);
                GameStateUtils::Draw(state);

                if (GameStateUtils::ShouldExit(state))
                {
                    app->running = false;
                }

                TimerUtils::Reset(app->timer);
            }
        }

        SDL_Quit();
        return true;
    }

} // namespace ApplicationUtils

    } // namespace system
} // namespace fob
