//-----------------------------------------------------------------------------
// Author: Aaron Oman
// Contact: aaron.oman@gmail.com
// Date: Oct 19 2009
//-----------------------------------------------------------------------------

#include "interface/frontend.h"
#include "system/config.h"
#include "system/frontendobjectmanager.h"
#include "system/soundmanager.h"
#include "system/texturemanager.h"
#include <SDL.h>

namespace fob {
    namespace interface {

        FrontEnd::FrontEnd(const char * path) :
            Interface(path)
        {
            using namespace fob::system;
            _id = Unique::Instance().Id();
            Config &cfg = Config::Instance();
            cfg.Activate("main");
            libconfig::Setting &w = cfg.Setting("application.window");
            _width = w["width"];
            _height = w["height"];
            _bg_scroll.Init(10);
            _x_coord = 0;
            _y_coord = 0;

            cfg.Load("frontend", path);
            try { 
                libconfig::Setting &s = cfg.Setting("in_game");
                _clear_color[0] = 0.45;
                _clear_color[1] = 0.45;
                _clear_color[2] = 0.45;
                _clear_color[3] = 1.0;
                _tex_width = s["tex_width"];
                _tex_height = s["tex_height"];
                _background_music = s["background"];
            } catch (libconfig::SettingNameException e) {
                printf("Setting Name Exception: %s\n", e.getPath());
            } catch (libconfig::SettingNotFoundException e) {
                printf("Setting Not Found Exception: %s\n", e.getPath());
            } catch (libconfig::SettingTypeException e) {
                printf("Setting Type Exception: %s\n", e.getPath());
            }

            InitGraphics();
            SoundManager::Instance().LoadFromCfg("frontend", _id);
            TextureManager::Instance().LoadFromCfg("frontend", _id);
            FrontEndObjectManager::Instance().Init("frontend");
            SoundManager::Instance().Loop(_background_music);

            try { 
                libconfig::Setting &s = cfg.Setting("in_game");
                _texture = TextureManager::Instance().Texture( s["texture"] );
                _tile = TextureManager::Instance().Texture( s["tile"] );
            } catch (libconfig::SettingNameException e) {
                printf("Setting Name Exception: %s\n", e.getPath());
            } catch (libconfig::SettingNotFoundException e) {
                printf("Setting Not Found Exception: %s\n", e.getPath());
            } catch (libconfig::SettingTypeException e) {
                printf("Setting Type Exception: %s\n", e.getPath());
            }
        }

        FrontEnd::~FrontEnd() {
            using namespace fob::system;
            FrontEndObjectManager::Destroy();
            SoundManager::Instance().Stop(_background_music);
            SoundManager::Instance().RemoveReferences(_id);
            TextureManager::Instance().RemoveReferences(_id);
        }

        void FrontEnd::Pause() {
        }

        void FrontEnd::UnPause() {
        }

        void FrontEnd::InitGraphics() {
            glClearColor(_clear_color[0], _clear_color[1], _clear_color[2], _clear_color[3]);
            glViewport(0, 0, _width, _height);
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            glOrtho(-_width/2, _width/2, -_height/2, _height/2, -1, 1);
            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();

            glEnable(GL_TEXTURE_2D);
            glDisable(GL_LIGHTING);
            glEnable(GL_DEPTH_TEST);
            glDepthFunc(GL_LEQUAL);
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        }

        void FrontEnd::Update() {
            fob::system::FrontEndObjectManager::Instance().Update();
            if (_bg_scroll.Expired()) {
                _x_coord += 0.01;
                _y_coord += 0.01;
                if (_x_coord > 1) _x_coord = 0.01;
                if (_y_coord > 1) _y_coord = 0.01;
                _bg_scroll.Reset();
            }
        }

        void FrontEnd::Draw() {
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glLoadIdentity();

            glBindTexture(GL_TEXTURE_2D, _tile);
            glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

            glBegin(GL_QUADS);
                glColor4f(1, 1, 1, 1);
                glTexCoord2f(_x_coord,    _y_coord + 1.95); glVertex3f(-_width/2, -_height/2, 0);
                glTexCoord2f(_x_coord,    _y_coord);    glVertex3f(-_width/2,  _height/2, 0);
                glTexCoord2f(_x_coord + 3.91, _y_coord);    glVertex3f( _width/2,  _height/2, 0);
                glTexCoord2f(_x_coord + 3.91, _y_coord + 1.95); glVertex3f( _width/2, -_height/2, 0);
            glEnd();

            glBindTexture(GL_TEXTURE_2D, _texture);
            glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

            glBegin(GL_QUADS);
                glColor4f(1, 1, 1, 1);
                glTexCoord2f(0,          _tex_height); glVertex3f(-_width/2, -_height/2, 0.0);
                glTexCoord2f(0,          0);           glVertex3f(-_width/2,  _height/2, 0.0);
                glTexCoord2f(_tex_width, 0);           glVertex3f( _width/2,  _height/2, 0.0);
                glTexCoord2f(_tex_width, _tex_height); glVertex3f( _width/2, -_height/2, 0.0);
            glEnd();

            fob::system::FrontEndObjectManager::Instance().Draw();

            SDL_GL_SwapBuffers();
        }

        void FrontEnd::HandleMessage(fob::system::Message &msg) {
            fob::system::FrontEndObjectManager::Instance().HandleMessage(msg);
        }

        bool FrontEnd::PauseEnabled() {
            return false;
        }

    } // namespace interface
} // namespace fob
