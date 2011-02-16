//-----------------------------------------------------------------------------
// Author: Aaron Oman
// Contact: aaron.oman@gmail.com
// Date: Oct 19 2009
//-----------------------------------------------------------------------------

#include "system/ingameobjectmanager.h"
#include "system/inputmanager.h"
#include "system/interfacemanager.h"
#include "system/messagequeue.h"
#include <SDL.h>

namespace fob {
    namespace system {

        InputManager& InputManager::Instance() {
            static InputManager singleton;
            return singleton;
        }

        InputManager::InputManager() {
        }

        InputManager::~InputManager() {
        }

        void InputManager::Update() {
            SDL_Event keyevent;
            while (SDL_PollEvent(&keyevent)) {
                if (keyevent.type == SDL_KEYDOWN) {
                    if (keyevent.key.keysym.sym == SDLK_ESCAPE) {
                        if (InterfaceManager::Instance().InPause()) {
                            MessageQueue::Instance().Broadcast(fob::system::Event::UNPAUSE, 0);
                        }
                        else if (InterfaceManager::Instance().PauseEnabled()) {
                            MessageQueue::Instance().Broadcast(fob::system::Event::PAUSE, 0);
                        }
                    }
                }
            }
        }

        InputManager::InputManager(const InputManager&) {
        }

        InputManager& InputManager::operator=(const InputManager&) {
            return *this;
        }

    } // namespace system
} // namespace fob
