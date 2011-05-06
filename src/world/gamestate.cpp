#include "world/gamestate.h"

#include <stdio.h>
#include <SDL.h>
#include <SDL_opengl.h>

namespace fob {
    namespace world {

namespace GameStateUtils
{
    //------------------------------------------------------------------------
    //
    void Update(GameState &state)
    {
        fob::input::InputUtils::Update(state.input, state);
        fob::world::PlayerUtils::Update(state.player, state);
    }

    //------------------------------------------------------------------------
    //
    void Draw(const GameState &state)
    {
        glClearColor(0.0, 0.0, 0.0, 1.0);
        // TODO: AOMAN: Need to synchronize this with ApplicationState
        // initialization!
        float width = 480;
        float height = 320;
        glViewport(0, 0, width, height);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(-(width/2), (width/2), -(height/2), (height/2), -1, 1);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        glDisable(GL_TEXTURE_2D);
        glShadeModel(GL_SMOOTH);
        glClearDepth(1.0);
        glDisable(GL_LIGHTING);
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LEQUAL);
        glEnable(GL_BLEND);
        glEnable(GL_POINT_SMOOTH);
        glFrontFace(GL_CW);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glLoadIdentity();

        fob::world::PlayerUtils::Draw(state.player, state);

        SDL_GL_SwapBuffers();
    }

    //------------------------------------------------------------------------
    //
    bool ShouldExit(const GameState &state)
    {
        return (state.input.action == fob::input::InputAction::Quit);
    }
}

    } // namespace world
} // namespace fob
