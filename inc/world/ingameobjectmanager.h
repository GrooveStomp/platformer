//-----------------------------------------------------------------------------
// Author: Aaron Oman
// Contact: aaron.oman@gmail.com
// Date: Oct 19 2009
//-----------------------------------------------------------------------------

#ifndef IN_GAME_OBJECT_MANAGER_H
#define IN_GAME_OBJECT_MANAGER_H

#include "system/messagequeue.h"
#include "system/objectmanager.h"
#include "system/timer.h"
#include "world/model/object.h"
#include "world/view/planet.h"
#include "world/view/player.h"
#include <vector>
#include <string>

namespace fob {

    namespace system {

        struct Player {
            fob::world::Object * _player;
            fob::world::Object * _planet;
        };

        class InGameObjectManager : ObjectManager {
            public:
                static InGameObjectManager& Instance();
                static void Destroy();
                void Init(std::string cfg_name);
                void Update();
                void HandleMessage(Message &msg);
                void Draw();
                void BorderRule(const char * rule, int index, float min, float max);
                fob::world::ViewControlPlayer* PlayerById(unsigned int id);
                fob::world::ViewControlPlanet* PlanetById(unsigned int id);
                fob::world::ViewControlPlanet* Planet(int index);
                std::vector<fob::world::Object*> Players();
                std::vector<fob::world::Object*> Planets();
                std::vector<fob::world::Object*> Objects();
                unsigned int PlayerIndex(unsigned int id);

            private:
                InGameObjectManager();
                InGameObjectManager(InGameObjectManager &);
                ~InGameObjectManager();

                fob::system::Player _player[2];
                std::vector<fob::world::Object*> _objects;

                Timer _shot_delay;
                std::string _cfg_name;
        };
    } // namespace system
} // namespace fob

#endif
