//-----------------------------------------------------------------------------
// Author: Aaron Oman
// Contact: aaron.oman@gmail.com
// Date: Oct 19 2009
//-----------------------------------------------------------------------------

#include "interface/hud.h"
#include "interface/ingame.h"
#include "system/config.h"
#include "system/font.h"
#include "system/ingameobjectmanager.h"
#include "system/soundmanager.h"
#include "system/texturemanager.h"
#include "world/view/player.h"
#include "world/view/sprite.h"
#include <SDL_opengl.h>

namespace fob {
    namespace interface {

        InGame::InGame(const char * path) :
            Interface(path),
            _counting(true),
            _pause_enabled(false),
            _counter_switch(false)
        {
            using namespace fob::system;
            _id = Unique::Instance().Id();
            Config &cfg = Config::Instance();
            cfg.Activate("main");
            try { 
                libconfig::Setting &w = cfg.Setting("application.window");
                _width = w["width"];
                _height = w["height"];
            } catch (libconfig::SettingNameException e) {
                printf("Setting Name Exception: %s\n", e.getPath());
            } catch (libconfig::SettingNotFoundException e) {
                printf("Setting Not Found Exception: %s\n", e.getPath());
            } catch (libconfig::SettingTypeException e) {
                printf("Setting Type Exception: %s\n", e.getPath());
            }

            cfg.Load("ingame", path);
            try { 
                libconfig::Setting &s = cfg.Setting("in_game");
                _x_rule = s["x_rule"];
                _y_rule = s["y_rule"];
                _clear_color[0] = 0.18;
                _clear_color[1] = 0.55;
                _clear_color[2] = 0.19;
                _clear_color[3] = 1.0;
                _count_down.Init( s["count_down"] );
                _countdown_sound = static_cast<const char *>(s["countdown_sound"]);
                _start_match_sound = static_cast<const char *>(s["start_match_sound"]);
            } catch (libconfig::SettingNameException e) {
                printf("Setting Name Exception: %s\n", e.getPath());
            } catch (libconfig::SettingNotFoundException e) {
                printf("Setting Not Found Exception: %s\n", e.getPath());
            } catch (libconfig::SettingTypeException e) {
                printf("Setting Type Exception: %s\n", e.getPath());
            }

            InitGraphics();
            SoundManager::Instance().LoadFromCfg("ingame", _id);
            TextureManager::Instance().LoadFromCfg("ingame", _id);
            InGameObjectManager::Instance().Init("ingame");
            SoundManager::Instance().Loop("data/snd/level_1_loop.wav");
            _hud = new Hud(cfg.Setting("hud"));

            try { 
                libconfig::Setting &s = cfg.Setting("in_game");
                _one = new fob::world::Sprite(s["one"]);
                _two = new fob::world::Sprite(s["two"]);
                _three = new fob::world::Sprite(s["three"]);
            } catch (libconfig::SettingNameException e) {
                printf("Setting Name Exception: %s\n", e.getPath());
            } catch (libconfig::SettingNotFoundException e) {
                printf("Setting Not Found Exception: %s\n", e.getPath());
            } catch (libconfig::SettingTypeException e) {
                printf("Setting Type Exception: %s\n", e.getPath());
            }
        }

        void InGame::InitGraphics() {
            glClearColor(_clear_color[0], _clear_color[1], _clear_color[2], _clear_color[3]);
            glViewport(0, 0, _width, _height);
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            glOrtho(-_width/2.0, _width/2.0, -_height/2.0, _height/2.0, -1, 1);
            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();

            glEnable(GL_TEXTURE_2D);
            glShadeModel(GL_SMOOTH);
            glClearDepth(1.0);
            glDisable(GL_LIGHTING);
            glEnable(GL_DEPTH_TEST);
            glDepthFunc(GL_LEQUAL);
            glEnable(GL_BLEND);
            glEnable(GL_POINT_SMOOTH);
            glFrontFace(GL_CW);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        }

        InGame::~InGame() {
            using namespace fob::system;
            InGameObjectManager::Destroy();
            SoundManager::Instance().Stop("data/snd/level_1_loop.wav");
            SoundManager::Instance().RemoveReferences(_id);
            TextureManager::Instance().RemoveReferences(_id);
            delete _hud;
            delete _one;
            delete _two;
            delete _three;
        }

        void InGame::Pause() {
            using namespace fob::system;
            SoundManager::Instance().Pause("data/snd/level_1_loop.wav");
            _hud->Pause();
        }

        void InGame::UnPause() {
            using namespace fob::system;
            SoundManager::Instance().UnPause("data/snd/level_1_loop.wav");
            InitGraphics();
            _hud->UnPause();
            _hud->Show();
        }

        void InGame::Update() {
            using namespace fob::system;
            if (_count_down.Expired()) {
                if (_counting) {
                    _hud->Start();
                    _counting = false;
                    SoundManager::Instance().Play(_start_match_sound);
                    _pause_enabled = true;
                }
                using namespace fob::system;
                InGameObjectManager::Instance().Update();
                InGameObjectManager::Instance().BorderRule(_x_rule, 0, -_width/2, _width/2);
                InGameObjectManager::Instance().BorderRule(_y_rule, 1, -_height/2, _height/2);
                _hud->Update();
            }
        }

        void InGame::Draw() {
            using namespace fob::system;
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glLoadIdentity();

            InGameObjectManager::Instance().Draw();
            _hud->Draw();

            if (!_count_down.Expired()) {
                int t = 3 - (_count_down.Elapsed() / 1000) + 1;
                if (t == 3) {
                    if (!_counter_switch) {
                        SoundManager::Instance().Play(_countdown_sound);
                        _counter_switch = !_counter_switch;
                    }
                    _three->Draw();
                }
                else if (t == 2) {
                    if (_counter_switch) {
                        SoundManager::Instance().Play(_countdown_sound);
                        _counter_switch = !_counter_switch;
                    }
                    _two->Draw();
                }
                else if (t == 1) {
                    if (!_counter_switch) {
                        SoundManager::Instance().Play(_countdown_sound);
                        _counter_switch = !_counter_switch;
                    }
                    _one->Draw();
                }
            }

            SDL_GL_SwapBuffers();
        }

        void InGame::HandleMessage(fob::system::Message &msg) {
            using namespace fob::system;
            InGameObjectManager::Instance().HandleMessage(msg);
            if (msg._event_id == fob::system::Event::GIVE) {
                _hud->Show();
            }
        }

        bool InGame::PauseEnabled() {
            return _pause_enabled;
        }

    } // namespace interface
} // namespace fob
