//-----------------------------------------------------------------------------
// Author: Aaron Oman
// Contact: aaron.oman@gmail.com
// Date: Oct 19 2009
//-----------------------------------------------------------------------------

#include "system/application.h"
#include "system/config.h"
#include "system/ingameobjectmanager.h"
#include "system/inputmanager.h"
#include "system/interfacemanager.h"
#include "system/messagequeue.h"
#include "system/soundmanager.h"
#include "system/texturemanager.h"

#include <SDL.h>
#include <SDL/SDL_image.h>
#include <SDL_opengl.h>

namespace fob {
    namespace system {

        Application::Application(std::string path) {
            _running = 1;
            fob::system::Config &cfg = Config::Instance();
            cfg.Load("main", path);

            const char * title;
            float framerate;
            try {
                // Initialize interface manager with paths to interface configurations.
                libconfig::Setting &setting = cfg.Setting("application");
                InterfaceManager::Instance().Init(setting);

                _width = setting["width"];
                _height = setting["height"];
                title = setting["title"];
                framerate = setting["framerate"];
                _skip_fe = setting["skip_fe"];
            } catch (libconfig::SettingNameException e) {
                printf("Setting Name Exception: %s\n", e.getPath());
            } catch (libconfig::SettingNotFoundException e) {
                printf("Setting Not Found Exception: %s\n", e.getPath());
            } catch (libconfig::SettingTypeException e) {
                printf("Setting Type Exception: %s\n", e.getPath());
            }

            _timer.Init(framerate);

            if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0)
            {
                printf("Unable to initialize SDL: %s\n", SDL_GetError());
            }

            SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
            SDL_Surface* screen = SDL_SetVideoMode(_width, _height, 16, SDL_OPENGL);
            if (!screen)
            {
                printf("Couldn't set %dx%d video mode: %s\n", _width, _height, SDL_GetError());
            }

            SDL_WM_SetCaption(title, title);

            SoundManager::Instance().Init("main");

            // Need to load textures after OpenGL initialization.
            if (_skip_fe) {
                InterfaceManager::Instance().DoInGame();
            }
            else {
                InterfaceManager::Instance().DoFrontEnd();
            }
        }

        int Application::Run() {
            _timer.Reset();

            while (_running) {
                if (_timer.Expired()) {
                    _timer.Reset();

                    InterfaceManager::Instance().Update();
                    InputManager::Instance().Update();

                    MessageQueue &msgs = MessageQueue::Instance();
                    while (!msgs.Empty()) {
                        Message &msg = msgs.Peek();
                        InterfaceManager::Instance().HandleMessage(msg);
                        if (msg._event_id == Event::EXIT) {
                            _running = 0;
                            break;
                        }
                        else if (msg._event_id == Event::MATCH_END) {
                            int spacemen1 = InGameObjectManager::Instance().Planet(0)->Spacemen();
                            int spacemen2 = InGameObjectManager::Instance().Planet(1)->Spacemen();
                            InterfaceManager::Instance().DoEndGame(spacemen1, spacemen2);
                        }
                        msgs.Next();
                    }
                }
            }
            SDL_Quit();
            return 1;
        }

    } // namespace system
} // namespace fob
