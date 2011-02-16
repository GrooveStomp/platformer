//-----------------------------------------------------------------------------
// Author: Aaron Oman
// Contact: aaron.oman@gmail.com
// Date: Oct 19 2009
//-----------------------------------------------------------------------------

#ifndef FRONT_END_OBJECT_MANAGER_H
#define FRONT_END_OBJECT_MANAGER_H

#include "world/view/button.h"
#include "system/messagequeue.h"
#include "system/objectmanager.h"
#include "system/timer.h"
#include <string>
#include <vector>

namespace fob {
    namespace system {

        class FrontEndObjectManager : ObjectManager {
            public:
                static FrontEndObjectManager& Instance();
                static void Destroy();
                void Init(std::string cfg_name);
                void Update();
                void HandleMessage(Message &msg);
                void Draw();

            private:
                FrontEndObjectManager();
                FrontEndObjectManager(FrontEndObjectManager &);
                ~FrontEndObjectManager();
                std::vector<fob::world::ViewControlButton> _buttons;
                std::string _cfg_name;
                int _active_button;
                Timer _key_timer;

                
        };
    } // namespace system
} // namespace fob

#endif
