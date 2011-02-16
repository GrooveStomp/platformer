//-----------------------------------------------------------------------------
// Author: Aaron Oman
// Contact: aaron.oman@gmail.com
// Date: Oct 19 2009
//-----------------------------------------------------------------------------

#include "interface/hud.h"
#include "system/config.h"
#include "system/ingameobjectmanager.h"
#include "system/messagequeue.h"
#include "system/soundmanager.h"

#ifndef foreach
#define foreach BOOST_FOREACH
#endif

namespace fob {
    namespace interface {

        Hud::Hud(libconfig::Setting &setting) :
            _bg(setting["sprite"]),
            _icon(setting["icon"]),
            _clock_sprite(setting["clock"]),
            _showing(true),
            _done_showing(false),
            _show(false),
            _clock_alpha(1.0),
            _end_match_sound_playing(false)
        {
            try {
                _show_timer.Init( setting["show_delay"] );
                _stay_timer.Init( setting["stay_time"] );
                _clock.Init( setting["level_time"] );
                libconfig::Setting &sp = setting["hide_position"];
                _hide_pos = fob::math::Vec2(sp[0], sp[1]);
                libconfig::Setting &ep = setting["show_position"];
                _show_pos = fob::math::Vec2(ep[0], ep[1]);
                _pos = fob::math::Vec2(_hide_pos[0], _hide_pos[1]);
                _end_match_sound = static_cast<const char *>(setting["end_match_sound"]);
            } catch (libconfig::SettingNameException e) {
                printf("Setting Name Exception: %s\n", e.getPath());
            } catch (libconfig::SettingNotFoundException e) {
                printf("Setting Not Found Exception: %s\n", e.getPath());
            } catch (libconfig::SettingTypeException e) {
                printf("Setting Type Exception: %s\n", e.getPath());
            }
        }

        void Hud::Start() {
            _show_timer.Reset();
            _clock.Reset();
            _show = true;
        }

        void Hud::Pause() {
            _clock.Pause();
        }

        void Hud::UnPause() {
            _clock.UnPause();
            Show();
        }

        void Hud::Show() {
            if (_showing) {
                _stay_timer.Reset();
            }
            else {
                _showing = true;
                _show_timer.Reset();
                _done_showing = false;
            }
        }

        void Hud::Hide() {
            if (_showing) {
                _showing = false;
                _show_timer.Reset();
            }
        }

        void Hud::Draw() {
            using namespace fob::system;
            if (_show) {
                char s[256];
                InGameObjectManager &objMgr = InGameObjectManager::Instance();
                glPushMatrix();
                glLoadIdentity();
                glTranslatef(_pos[0], _pos[1], 0);
                _bg.Draw();
                glTranslatef(0, 10, 0);
                _icon.Draw();
                _clock_sprite.Draw();

                sprintf(s, "%d", objMgr.Planet(0)->Spacemen());
                Font f("ingame", 1, 1, 1, 1, _pos[0]-200, _pos[1]-10, s);
                f.Draw();

                sprintf(s, "%d", objMgr.Planet(1)->Spacemen());
                Font f2("ingame", 1, 1, 1, 1, _pos[0]+200, _pos[1]-10, s, Font::ALIGN_RIGHT);
                f2.Draw();

                CalculateTime(&s[0]);
                Font clock("ingame", 1, 1, 1, _clock_alpha, 45, -210, s, Font::ALIGN_RIGHT, 30);
                clock.Draw();

                glPopMatrix();
            }
        }

        const char * Hud::CalculateTime(char * s) {
            int minutes = _clock.Length() - _clock.Elapsed();
            int seconds = minutes;

            minutes /= (1000 * 60);
            seconds /= (1000);
            seconds %= 60;
            sprintf(s, "%.2d:%.2d", minutes, seconds);
            return s;
        }

        void Hud::Update() {
            using namespace fob::system;
            if (!_show_timer.Expired()) {
                float lerp = _show_timer.Elapsed() / _show_timer.Length();
                if (!_showing) {
                    lerp = 1 - lerp;
                }
                _pos = Lerp(lerp);
            }
            if (_showing && _show_timer.Expired() && !_done_showing) {
                _done_showing = true;
                _stay_timer.Reset();
            }
            if (_done_showing && _stay_timer.Expired()) {
                Hide();
                _done_showing = false;
            }
            if (_clock.Elapsed() > _clock.Length() - 150 && !_end_match_sound_playing) {
                SoundManager::Instance().Play(_end_match_sound);
                _end_match_sound_playing = true;
            }
            if (_clock.Expired()) {
                MessageQueue::Instance().Broadcast(Event::MATCH_END, 0, 0);
            }
           
            _clock_alpha = 1.0;
            std::vector<fob::world::Object*> players = InGameObjectManager::Instance().Players();
            foreach(fob::world::Object *player, players) {
                if (_clock_sprite.Collide(player)) {
                    _clock_alpha = 0.2;
                }
            }
            _clock_sprite.SetTransparency(_clock_alpha);
        }

        fob::math::Vec2 Hud::Lerp(float lerp) {
            return _hide_pos + ( (_show_pos - _hide_pos) * lerp );
        }

    } // namespace interface
} // namespace fob
