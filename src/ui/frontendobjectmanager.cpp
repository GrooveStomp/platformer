//-----------------------------------------------------------------------------
// Author: Aaron Oman
// Contact: aaron.oman@gmail.com
// Date: Oct 19 2009
//-----------------------------------------------------------------------------

#include "system/frontendobjectmanager.h"

#include "system/config.h"
#include "system/messagequeue.h"
#include "system/soundmanager.h"
#include "system/texturemanager.h"

#include <SDL.h>
#include <string>

namespace fob {
    namespace system {

        static FrontEndObjectManager::FrontEndObjectManager * _singleton;

        FrontEndObjectManager& FrontEndObjectManager::Instance() {
            if (!_singleton) {
                _singleton = new FrontEndObjectManager();
            }
            return *_singleton;
        }

        void FrontEndObjectManager::Destroy() {
            delete _singleton;
            _singleton = 0;
        }

        FrontEndObjectManager::~FrontEndObjectManager() {
        }

        FrontEndObjectManager::FrontEndObjectManager() :
            _active_button(0)
        {
        }

        void FrontEndObjectManager::Init(std::string cfg_name) {
            _cfg_name = cfg_name;
            Config &cfg = Config::Instance();
            cfg.Activate(_cfg_name);
            try {
                libconfig::Setting &button = cfg.Setting("buttons");
                for (int i=0; i < button.getLength(); ++i) {
                    _buttons.push_back( fob::world::ViewControlButton(button[i]) );
                }
                libconfig::Setting &s = cfg.Setting("in_game");
                _key_timer.Init( s["key_timeout"] );
            } catch (libconfig::SettingNameException e) {
                printf("Setting Name Error: %s\n", e.getPath());
            } catch (libconfig::SettingNotFoundException e) {
                printf("Setting Not Found Error: %s\n", e.getPath());
            } catch (libconfig::SettingTypeException e) {
                printf("Setting Type Exception Error: %s\n", e.getPath());
            }
        }

        void FrontEndObjectManager::Update() {
            Uint8 * keys = SDL_GetKeyState(NULL);

            if (_key_timer.Expired()) {
                if (keys[SDLK_UP]) {
                    SoundManager::Instance().Play("data/snd/select.wav");
                    --_active_button;
                    if (_active_button < 0) {
                        _active_button = 0;
                    }
                }
                if (keys[SDLK_DOWN]) {
                    SoundManager::Instance().Play("data/snd/select.wav");
                    ++_active_button;
                    if (static_cast<unsigned int>(_active_button) >= _buttons.size()) {
                        _active_button = static_cast<int>(_buttons.size())-1;
                    }
                }
                if (keys[SDLK_RETURN]) {
                    SoundManager::Instance().Play("data/snd/enter.wav");
                    int idx = 0;
                    for (std::vector<fob::world::ViewControlButton>::iterator i=_buttons.begin(); i!=_buttons.end(); ++i, ++idx) {
                        if (idx == _active_button) {
                            MessageQueue::Instance().Broadcast(fob::system::Event::ACTIVATE, _buttons[idx].Id());
                            break;
                        }
                    }
                }
                int idx = 0;
                for (std::vector<fob::world::ViewControlButton>::iterator i=_buttons.begin(); i!=_buttons.end(); ++i, ++idx) {
                    _buttons[idx].Status(fob::world::ControlButton::STATUS_NONE);
                }
                _buttons[_active_button].Status(fob::world::ControlButton::STATUS_HOVER);
                _key_timer.Reset();
            }

            /*
            foreach (fob::world::ViewControlButton &button, _buttons) {
                button.Update();
            }
            */
        }

        void FrontEndObjectManager::HandleMessage(Message &msg) {
            /*
            foreach (fob::world::ViewControlButton &button, _buttons) {
                button.HandleMessage(msg);
            }
            */
        }

        void FrontEndObjectManager::Draw() {
            /*
            foreach (fob::world::ViewControlButton &button, _buttons) {
                button.Draw();
            }
            */
        }

        FrontEndObjectManager::FrontEndObjectManager(FrontEndObjectManager &) {
        }

    } // namespace system
} // namespace fob
