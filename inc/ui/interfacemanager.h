//-----------------------------------------------------------------------------
// Author: Aaron Oman
// Contact: aaron.oman@gmail.com
// Date: Oct 19 2009
//-----------------------------------------------------------------------------

#ifndef INTERFACE_MANAGER_H
#define INTERFACE_MANAGER_H

#include "system/messagequeue.h"
#include <vector>
#include <string>
#include <libconfig.h++>

namespace fob {

    namespace interface {
        class Interface;
    }

    namespace system {

        class InterfaceManager {
            public:
                static InterfaceManager& Instance();
                void Init(libconfig::Setting &setting);
                void Update();
                void HandleMessage(Message &msg);
                void DoFrontEnd();
                void DoInGame();
                void DoPause();
                void EndPause();
                bool InPause();
                bool PauseEnabled();
                void DoEndGame(int p1_score, int p2_score);

            private:
                InterfaceManager();
                InterfaceManager(InterfaceManager&);
                ~InterfaceManager();
                fob::interface::Interface * _interface;
                fob::interface::Interface * _background;
                std::string _pause_path;
                std::string _front_end_path;
                std::string _in_game_path;
                std::string _end_game_path;
                bool _in_game;
        };
    } // namespace system
} // namespace fob

#endif
