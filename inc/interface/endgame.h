//-----------------------------------------------------------------------------
// Author: Aaron Oman
// Contact: aaron.oman@gmail.com
// Date: Oct 19 2009
//-----------------------------------------------------------------------------

#ifndef END_GAME_H
#define END_GAME_H

#include "interface/interface.h"
#include "system/timer.h"
#include <SDL_opengl.h>

namespace fob {
    namespace interface {

        class EndGame : public Interface {
            public:
                EndGame(const char * path);
                virtual ~EndGame();
                virtual void Update();
                virtual void Draw();
                virtual void HandleMessage(fob::system::Message &msg);
                virtual void InitGraphics();
                virtual void Pause();
                virtual void UnPause();
                virtual bool PauseEnabled();
                void Scores(int score1, int score2);

            protected:
                GLuint _texture;
                GLuint _tile;
                float _tex_width;
                float _tex_height;
                const char * _background_music;
                fob::system::Timer _bg_scroll;
                float _x_coord;
                float _y_coord;
                int _score1;
                int _score2;
        };

    } // namespace interface
} // namespace fob

#endif
