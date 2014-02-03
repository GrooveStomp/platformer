#include "input/input.h"

#include "world/gamestate.h"

#include <SDL.h>

namespace fob {
    namespace input {

namespace InputUtils {

    void Update(InputState& input, const QueueState& readQueue, QueueNotifierState& writeQueue)
    {
        using namespace fob::system::QueueNotifierUtils;

        SDL_Event keyevent;
        while (SDL_PollEvent(&keyevent)) {
            if (keyevent.type == SDL_KEYDOWN) {
                if (keyevent.key.keysym.sym == SDLK_ESCAPE) {
                    Send(writeQueue, InputAction::Quit);
                }
                else if (keyevent.key.keysym.sym == SDLK_LEFT) {
                    Send(writeQueue, InputAction::Left);
                }
                else if (keyevent.key.keysym.sym == SDLK_RIGHT) {
                    Send(writeQueue, InputAction::Right);
                }
                else if (keyevent.key.keysym.sym == SDLK_UP) {
                    Send(writeQueue, InputAction::Up);
                }
                else if (keyevent.key.keysym.sym == SDLK_DOWN) {
                    Send(writeQueue, InputAction::Down);
                }
                else if (keyevent.key.keysym.sym == SDLK_SPACE) {
                    Send(writeQueue, InputAction::Jump);
                }
            }
        }
    }
}

    } // namespace input
} // namespace fob
