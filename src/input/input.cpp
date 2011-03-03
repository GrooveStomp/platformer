#include "input/input.h"

#include "world/gamestate.h"

#include <SDL.h>

namespace fob {
    namespace input {

namespace InputUtils
{
    //------------------------------------------------------------------------
    //
    InputState Update(const fob::world::GameState &state)
    {
        InputState input;

        SDL_Event keyevent;
        while (SDL_PollEvent(&keyevent)) {
            if (keyevent.type == SDL_KEYDOWN) {
                if (keyevent.key.keysym.sym == SDLK_ESCAPE) {
                    input = InputState(InputAction::Quit);
                }
                else if (keyevent.key.keysym.sym == SDLK_LEFT) {
                    input = InputState(InputAction::Left);
                }
                else if (keyevent.key.keysym.sym == SDLK_RIGHT) {
                    input = InputState(InputAction::Right);
                }
                else if (keyevent.key.keysym.sym == SDLK_SPACE) {
                    input = InputState(InputAction::Jump);
                }
            } else {
                input = InputState(InputAction::None);
            }
        }

        return input;
    }
}

    } // namespace input
} // namespace fob
