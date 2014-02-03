//-----------------------------------------------------------------------------
// Author: Aaron Oman
// Contact: aaron.oman@gmail.com
// Date: Oct 19 2009
//-----------------------------------------------------------------------------

#ifndef HUD_H
#define HUD_H

#include "system/font.h"
#include "system/timer.h"
#include "world/view/sprite.h"
#include <libconfig.h++>
#include <string>

namespace fob {
    namespace ui {

        class Hud {
            public:
                Hud(libconfig::Setting &setting);
                void Show();
                void Hide();
                void Draw();
                void Update();
                void Start();
                void Pause();
                void UnPause();

            private:
                const char * CalculateTime(char * s);
                fob::math::Vec2 Lerp(float lerp);
                fob::world::Sprite _bg;
                fob::world::Sprite _icon;
                fob::world::Sprite _clock_sprite;
                fob::system::Timer _show_timer;
                fob::system::Timer _stay_timer;
                fob::system::Timer _clock;
                fob::math::Vec2 _hide_pos;
                fob::math::Vec2 _show_pos;
                fob::math::Vec2 _pos;
                bool _showing;
                bool _done_showing;
                bool _show;
                float _clock_alpha;
                std::string _end_match_sound;
                bool _end_match_sound_playing;
        };

    } // namespace ui
} // namespace fob

#endif
