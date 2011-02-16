//-----------------------------------------------------------------------------
// Author: Aaron Oman
// Contact: aaron.oman@gmail.com
// Date: Oct 19 2009
//-----------------------------------------------------------------------------

#ifndef FRONT_END_H
#define FRONT_END_H

#include "interface/interface.h"
#include "system/timer.h"
#include <SDL_opengl.h>

namespace fob {
    namespace interface {

        class FrontEnd : public Interface {
            public:
                FrontEnd(const char * path);
                virtual ~FrontEnd();
                virtual void Update();
                virtual void Draw();
                virtual void HandleMessage(fob::system::Message &msg);
                virtual void InitGraphics();
                virtual void Pause();
                virtual void UnPause();
                virtual bool PauseEnabled();

            protected:
                GLuint _texture;
                GLuint _tile;
                float _tex_width;
                float _tex_height;
                const char * _background_music;
                fob::system::Timer _bg_scroll;
                float _x_coord;
                float _y_coord;
        };

    } // namespace interface
} // namespace fob

#endif
