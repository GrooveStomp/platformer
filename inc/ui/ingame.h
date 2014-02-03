//-----------------------------------------------------------------------------
// Author: Aaron Oman
// Contact: aaron.oman@gmail.com
// Date: Oct 19 2009
//-----------------------------------------------------------------------------

#ifndef IN_GAME_H
#define IN_GAME_H

#include "ui/interface.h"
#include "system/timer.h"
#include <string>

namespace fob {
    namespace world {
        class Sprite;
    }

    namespace ui {

        class Hud;

        class InGame : public Interface {
            public:
                InGame(const char * path);
                virtual ~InGame();
                virtual void Update();
                virtual void Draw();
                virtual void HandleMessage(fob::system::Message &msg);
                virtual void InitGraphics();
                virtual void Pause();
                virtual void UnPause();
                virtual bool PauseEnabled();

            protected:
                const char * _x_rule;
                const char * _y_rule;
                Hud * _hud;
                fob::system::Timer _count_down;
                bool _counting;
                fob::world::Sprite * _one;
                fob::world::Sprite * _two;
                fob::world::Sprite * _three;
                bool _pause_enabled;
                std::string _countdown_sound;
                std::string _start_match_sound;
                bool _counter_switch;
        };

    } // namespace interface
} // namespace fob

#endif
