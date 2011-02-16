//-----------------------------------------------------------------------------
// Author: Aaron Oman
// Contact: aaron.oman@gmail.com
// Date: Oct 19 2009
//-----------------------------------------------------------------------------

#include "interface/endgame.h"
#include "interface/frontend.h"
#include "interface/ingame.h"
#include "interface/interface.h"
#include "system/interfacemanager.h"

namespace fob {
    namespace system {

        InterfaceManager& InterfaceManager::Instance() {
            static InterfaceManager singleton;
            return singleton;
        }

        InterfaceManager::InterfaceManager() {
            _background = 0;
            _interface = 0;
            _in_game = false;
        }

        InterfaceManager::InterfaceManager(InterfaceManager&) {
        }

        InterfaceManager::~InterfaceManager() {
            if (_interface) {
                delete _interface;
            }
            if (_background) {
                delete _background;
            }
        }

        void InterfaceManager::Init(libconfig::Setting &setting) {
            _pause_path = static_cast<const char *>( setting["pause"] );
            _front_end_path = static_cast<const char *>( setting["front_end"] );
            _in_game_path = static_cast<const char *>( setting["in_game"] );
            _end_game_path = static_cast<const char *>( setting["end_game"] );
        }

        void InterfaceManager::Update() {
            _interface->Draw();
            _interface->Update();
        }

        void InterfaceManager::HandleMessage(Message &msg) {
            _interface->HandleMessage(msg);

            if (msg._event_id == Event::PAUSE) {
                DoPause();
            }
            if (msg._event_id == Event::UNPAUSE) {
                EndPause();
            }
            if (msg._event_id == Event::START) {
                DoInGame();
            }
            if (msg._event_id == Event::TOFE) {
                DoFrontEnd();
            }
        }

        void InterfaceManager::DoFrontEnd() {
            if (_interface) {
                delete _interface;
            }
            if (_background) {
                delete _background;
                _background = 0;
            }
            _interface = new fob::interface::FrontEnd(_front_end_path.c_str());
            _in_game = false;
        }

        void InterfaceManager::DoInGame() {
            if (_interface) {
                delete _interface;
            }
            _interface = new fob::interface::InGame(_in_game_path.c_str());
            _in_game = true;
        }

        void InterfaceManager::DoEndGame(int p1_score, int p2_score) {
            if (_interface) {
                delete _interface;
            }
            _interface = new fob::interface::EndGame(_end_game_path.c_str());
            dynamic_cast<fob::interface::EndGame*>(_interface)->Scores(p1_score, p2_score);
            _in_game = false;
        }

        void InterfaceManager::DoPause() {
            if (!_background) {
                _background = _interface;
                _background->Pause();
                _interface = new fob::interface::FrontEnd(_pause_path.c_str());
            }
        }

        void InterfaceManager::EndPause() {
            // Ensure our normal interface is saved
            // in _background before reverting.
            if (_background) {
                delete _interface;
                _interface = _background;
                _background = 0;
                _interface->UnPause();
            }
        }

        bool InterfaceManager::InPause() {
            return _background != 0;
        }

        bool InterfaceManager::PauseEnabled() {
            return _interface->PauseEnabled();
        }

    } // namespace system
} // namespace fob
