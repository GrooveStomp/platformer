//-----------------------------------------------------------------------------
// Author: Aaron Oman
// Contact: aaron.oman@gmail.com
// Date: Oct 19 2009
//-----------------------------------------------------------------------------

#include "system/config.h"
#include "system/ingameobjectmanager.h"
#include "system/messagequeue.h"
#include "system/texturemanager.h"
#include "world/model/object.h"
#include "world/view/particle.h"
#include "world/view/planet.h"
#include "world/view/player.h"
#include "world/view/shot.h"
#include "world/view/spaceman.h"
#include "world/view/sprite.h"
#include <math.h>
#include <string>

#ifndef PI
#define PI 3.14159
#endif

namespace fob {
    namespace system {

        static InGameObjectManager::InGameObjectManager * singleton = 0;

        InGameObjectManager& InGameObjectManager::Instance() {
            if (!singleton) {
                singleton = new InGameObjectManager();
            }
            return *singleton;
        }

        void InGameObjectManager::Destroy() {
            delete singleton;
            singleton = 0;
        }

        InGameObjectManager::~InGameObjectManager() {
            for (unsigned int i = 0; i < _objects.size(); ++i) {
                delete _objects[i];
            }
            _objects.clear();
        }

        InGameObjectManager::InGameObjectManager() {
            srand(_shot_delay.Elapsed());
        }

        void InGameObjectManager::Init(std::string cfg_name) {
            _cfg_name = cfg_name;
            Config::Instance().Activate(_cfg_name);

            libconfig::Setting &players = Config::Instance().Setting("players");
            for (int i=0; i < players.getLength(); ++i) {
                _player[i]._player = new fob::world::ViewControlPlayer( players[i] );
            }

            libconfig::Setting &planets = Config::Instance().Setting("planets");
            for (int i=0; i < planets.getLength(); ++i) {
                _objects.push_back(
                    new fob::world::ViewControlPlanet(
                        planets[i],
                        _player[i]._player->Id(),
                        _player[1-i]._player->Id()
                    )
                );
                _player[i]._planet = _objects[_objects.size()-1];
            }
            
            for (int i=0; i < 2; ++i) {
                _objects.push_back(_player[i]._player);
            }

            try {
                libconfig::Setting &s = Config::Instance().Setting("general");
                _shot_delay.Init( s["shot_delay"] );
            } catch (libconfig::SettingNameException e) {
                const char * error = e.getPath();
                printf("Setting Name Error: %s\n", error);
            } catch (libconfig::SettingNotFoundException e) {
                const char * error = e.getPath();
                printf("Setting Not Found Error: %s\n", error);
            } catch (libconfig::SettingTypeException e) {
                const char * error = e.getPath();
                printf("Setting Type Exception Error: %s\n", error);
            }
        }

        fob::world::ViewControlPlayer* InGameObjectManager::PlayerById(unsigned int id) {
            using namespace fob::world;
            if (_player[0]._player->Id() == id) {
                return dynamic_cast<ViewControlPlayer*>(_player[0]._player);
            }
            return dynamic_cast<ViewControlPlayer*>(_player[1]._player);
        }

        fob::world::ViewControlPlanet* InGameObjectManager::PlanetById(unsigned int id) {
            using namespace fob::world;
            if (_player[0]._planet->Id() == id) {
                return dynamic_cast<ViewControlPlanet*>(_player[0]._planet);
            }
            return dynamic_cast<ViewControlPlanet*>(_player[1]._planet);
        }

        fob::world::ViewControlPlanet* InGameObjectManager::Planet(int index) {
            using namespace fob::world;
            return dynamic_cast<ViewControlPlanet*>(_player[index]._planet);
        }

        void InGameObjectManager::Update() {
            using namespace fob::world;
            Uint8 * keystates = SDL_GetKeyState(NULL);

            // Handle all input.
            for (int i=0; i<2; ++i) {
                dynamic_cast<ViewControlPlayer*>(_player[i]._player)->HandleInput(keystates);
            }

            // Update all objects.
            /*
            foreach (Object * obj, _objects) {
                obj->Update();
            }
            */
        }

        void InGameObjectManager::HandleMessage(Message &msg) {
            Config::Instance().Activate("ingame");
            if (msg._event_id == Event::SHOOT && _shot_delay.Expired()) { // a shot has been fired
                fob::world::ViewControlPlayer *p = PlayerById(msg._initiator_id);

                float r = p->Rotation();
                fob::math::Vec2 d( cos(r / 180 * PI), sin(r / 180 * PI));
                d.Normalize();

                fob::math::Vec2 pos = p->Position() + d * (p->Width()*3/4);
                Config::Instance().Activate(_cfg_name.c_str());
                _objects.push_back(
                    new fob::world::ViewControlShot(Config::Instance().Setting("shot"), pos, r)
                );
                _shot_delay.Reset();
            }

            if (msg._event_id == Event::EXPLODE && 
                    (
                        msg._recipient_id == _player[0]._player->Id() ||
                        msg._recipient_id == _player[1]._player->Id()
                    )
               ) {
                int num_explosions = rand() % 5 + 3;
                float angle = 360 / num_explosions;
                for (int i=0; i<num_explosions; ++i) {
                    float rot = angle * i;
                    fob::math::Vec2 d( cos(rot / 180 * PI), sin(rot / 180 * PI));
                    d.Normalize();
                    fob::math::Vec2 p = PlayerById(msg._initiator_id)->Position() + (d * (rand() % 40 + 1));
                    _objects.push_back(
                        new fob::world::Particle(Config::Instance().Setting("particle"), p, rand() % 3 - 1, rand() % 360)
                    );
                }
            }
            else if (msg._event_id == Event::EXPLODE) {
                Config::Instance().Activate("ingame");
                float rotation = 360 / 5 * (rand() % 5 + 1);
                fob::math::Vec2 d( cos(rotation / 180 * PI), sin(rotation / 180 * PI));
                d.Normalize();
                fob::math::Vec2 p = PlayerById(msg._initiator_id)->Position() + (d * (rand() % 75 + 1));
                _objects.push_back(
                    new fob::world::ViewControlSpaceman(Config::Instance().Setting("spaceman"), p, msg._recipient_id)
                );
            }
            else if (msg._event_id == Event::HIT) {
                fob::math::Vec2 p = PlayerById(msg._recipient_id)->Position();
                _objects.push_back(new fob::world::Particle(
                    Config::Instance().Setting("particle"),
                    p,
                    rand() % 3 - 1,
                    rand() % 360
                ));
            }
            else if (msg._event_id == Event::DIE) { // need to remove an object
                for (unsigned int i=0; i<_objects.size(); ++i) {
                    if (_objects[i]->Id() == msg._recipient_id) {
                        _objects.erase(_objects.begin() + i);
                        break;
                    }
                }
            }

            /*
            foreach (fob::world::Object * obj, _objects) {
                obj->HandleMessage(msg);
            }
            */
        }

        void InGameObjectManager::Draw() {
            /*
            foreach (fob::world::Object * obj, _objects) {
                obj->Draw();
            }
            */
        }

        std::vector<fob::world::Object*> InGameObjectManager::Players() {
            using namespace fob::world;
            std::vector<Object*> v;
            v.push_back(_player[0]._player);
            v.push_back(_player[1]._player);
            return v;
        }

        std::vector<fob::world::Object*> InGameObjectManager::Planets() {
            using namespace fob::world;
            std::vector<Object*> v;
            v.push_back(_player[0]._planet);
            v.push_back(_player[1]._planet);
            return v;
        }

        std::vector<fob::world::Object*> InGameObjectManager::Objects() {
            return _objects;
        }

        unsigned int InGameObjectManager::PlayerIndex(unsigned int id) {
            if (_player[0]._player->Id() == id) {
                return 0;
            }
            return 1;
        }

        void InGameObjectManager::BorderRule(const char * rule, int index, float min, float max) {
            std::string r = rule;
            if (r == "open") return;

            /*
            foreach (fob::world::Object * obj, _objects) {
                float size = obj->Width();
                if (index) size = obj->Height();

                if (obj->Position()[index] > max + size && r == "wrap") {
                    obj->Position()[index] = min;
                }
                else if (obj->Position()[index] > max - size/2 && r == "clamp") {
                    obj->Position()[index] = max - size/2;
                    if (obj->Type() == fob::world::Object::TYPE_SHOT) {
                        MessageQueue::Instance().Broadcast(fob::system::Event::DIE, obj->Id());
                    }
                }
                if (obj->Position()[index] < min - size && r == "wrap") {
                    obj->Position()[index] = max;
                }
                else if (obj->Position()[index] < min + size/2 && r == "clamp") {
                    obj->Position()[index] = min + size/2;
                    if (obj->Type() == fob::world::Object::TYPE_SHOT) {
                        MessageQueue::Instance().Broadcast(fob::system::Event::DIE, obj->Id());
                    }
                }
            }
            */
        }

        InGameObjectManager::InGameObjectManager(InGameObjectManager &) {
        }

    } // namespace system
} // namespace fob
