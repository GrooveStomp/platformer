#include "input/input.h"

#include "world/gamestate.h"

#include <SDL.h>

namespace fob {
    namespace input {

namespace InputUtils {

    void Update(InputState* const input, const QueueState* const messageQueue, QueueNotifierState* const messageNotifier)
    {
        using namespace fob::system::QueueNotifierUtils;

        SDL_Event keyevent;
        while (SDL_PollEvent(&keyevent)) {
            if (keyevent.type == SDL_KEYDOWN) {
                if (keyevent.key.keysym.sym == SDLK_ESCAPE) {
                    Send(messageNotifier, InputAction::Quit);
                }
                else if (keyevent.key.keysym.sym == SDLK_LEFT) {
                    Send(messageNotifier, InputAction::Left);
                }
                else if (keyevent.key.keysym.sym == SDLK_RIGHT) {
                    Send(messageNotifier, InputAction::Right);
                }
                else if (keyevent.key.keysym.sym == SDLK_UP) {
                    Send(messageNotifier, InputAction::Up);
                }
                else if (keyevent.key.keysym.sym == SDLK_DOWN) {
                    Send(messageNotifier, InputAction::Down);
                }
                else if (keyevent.key.keysym.sym == SDLK_SPACE) {
                    Send(messageNotifier, InputAction::Jump);
                }
            }
        }
    }
}

    } // namespace input
} // namespace fob
