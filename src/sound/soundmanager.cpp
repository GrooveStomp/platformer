//-----------------------------------------------------------------------------
// Author: Aaron Oman
// Contact: aaron.oman@gmail.com
// Date: Oct 19 2009
//-----------------------------------------------------------------------------

#include "system/soundmanager.h"

#include "system/config.h"
#include <iostream>

namespace fob {
    namespace system {

        Mix_Chunk* SoundObject::Data() {
            return _sound;
        }

        SoundObject::SoundObject(std::string name) {
            _name = name;
            _sound = Mix_LoadWAV( name.c_str() );
            if (_sound == NULL) {
                printf("Error loading file %s: %s\n", name.c_str(), Mix_GetError());
            }
        }

        SoundObject::~SoundObject() {
            Mix_FreeChunk(_sound);
        }

        void SoundObject::AddReference(unsigned int id) {
            if (!HasReference(id)) {
                _references.push_back(id);
            }
        }

        void SoundObject::RemoveReference(unsigned int id) {
            unsigned int i=0, found=0;
            for (i=0; i<_references.size(); ++i) {
                if (_references[i] == id) {
                    found = 1;
                    break;
                }
            }
            if (found) _references.erase(_references.begin() + i);
        }

        bool SoundObject::HasReference(unsigned int id) {
            for (unsigned int i=0; i<_references.size(); ++i) {
                if (_references[i] == id) {
                    return true;
                }
            }
            return false;
        }

        bool SoundObject::HasReferences() {
            return _references.size();
        }

        std::string SoundObject::Name() {
            return _name;
        }

// ----------------------------------------------------------------------------

        SoundManager::SoundManager() {
        }

        SoundManager::~SoundManager() {
            for (unsigned int i=0; i<_sounds.size(); ++i) {
                delete _sounds[i];
            }
            _sounds.clear();
            Mix_CloseAudio();
        }

        SoundManager& SoundManager::Instance() {
            static SoundManager singleton;
            return singleton;
        }

        bool SoundManager::Init(std::string cfg_name) {
            Config::Instance().Activate(cfg_name);
            try {
                libconfig::Setting &setting = Config::Instance().Setting("sound_setup");
                _rate = setting["rate"];
                _format = AUDIO_S16SYS;
                _num_channels = setting["channels"];
                _chunk_size = setting["chunk_size"];
            } catch (libconfig::SettingNameException e) {
                printf("Setting Name Exception: %s\n", e.getPath());
            } catch (libconfig::SettingNotFoundException e) {
                printf("Setting Not Found Exception: %s\n", e.getPath());
            } catch (libconfig::SettingTypeException e) {
                printf("Setting Type Exception: %s\n", e.getPath());
            }

            if (Mix_OpenAudio(_rate, _format, _num_channels, _chunk_size) != 0) {
                printf("Error initializing audio: %s\n", Mix_GetError());
                exit(1);
            }

            return 1;
        }

        bool SoundManager::Load(std::string path, unsigned int id) {
            // First check if the sound already exists.
            for (unsigned int i=0; i<_sounds.size(); ++i) {
                if (_sounds[i]->Name() == path) {
                    _sounds[i]->AddReference(id);
                    return true;
                }
            }

            // The texture doesn't exist yet, so create it.
            _sounds.push_back(new SoundObject(path));
            _sounds[_sounds.size()-1]->AddReference(id);
            return true;
        }

        int SoundObject::References() {
            return _references.size();
        }

        bool SoundManager::LoadFromCfg(std::string cfg_name, unsigned int id) {
            Config::Instance().Activate(cfg_name);
             try {
                libconfig::Setting &setting = Config::Instance().Setting("sounds");
                int num_sounds = setting.getLength();

                for (int i=0; i<num_sounds; ++i) {
                    if (!Load(setting[i], id)) {
                        return false;
                    }
                }
            } catch (libconfig::SettingNameException e) {
                printf("Setting Name Exception: %s\n", e.getPath());
            } catch (libconfig::SettingNotFoundException e) {
                printf("Setting Not Found Exception: %s\n", e.getPath());
            } catch (libconfig::SettingTypeException e) {
                printf("Setting Type Exception: %s\n", e.getPath());
            }

            return true;
        }

        int SoundManager::IndexOf(std::string path) {
            for (unsigned int i=0; i<_sounds.size(); ++i) {
                if (_sounds[i]->Name() == path) {
                    return i;
                }
            }
            return -1;
        }

        bool SoundManager::Play(std::string path) {
            int i = IndexOf(path);
            int channel = Mix_PlayChannel(-1, _sounds[i]->Data(), 0);
            if (channel == -1) {
                printf("Error playing file %s: %s\n", path.c_str(), Mix_GetError());
                return 0;
            }
            _channels[path] = channel;
            return 1;
        }

        bool SoundManager::Loop(std::string path, int loops) {
            int i = IndexOf(path);
            loops = !loops ? -1 : loops;
            int channel = Mix_PlayChannel(-1, _sounds[i]->Data(), loops);
            if (channel == -1) {
                printf("Error playing file %s: %s\n", path.c_str(), Mix_GetError());
                return 0;
            }
            _channels[path] = channel;
            return 1;
        }

        bool SoundManager::Stop(std::string path) {
            return Mix_FadeOutChannel(_channels[path.c_str()], 100);
        }

        void SoundManager::Pause(std::string path) {
            Mix_Pause(_channels[path.c_str()]);
        }

        void SoundManager::UnPause(std::string path) {
            Mix_Resume(_channels[path.c_str()]);
        }

        void SoundManager::RemoveReferences(unsigned int id) {
            for (unsigned int i=0; i<_sounds.size(); ++i) {
                _sounds[i]->RemoveReference(id);
            }

            std::vector<int> idx;
            for (unsigned int i=0; i<_sounds.size(); ++i) {
                if (!_sounds[i]->HasReferences()) {
                    delete _sounds[i];
                    idx.push_back(i);
                }
            }

            for (int i = idx.size()-1; i >= 0; --i) {
                _sounds.erase( _sounds.begin()+idx[i] );
            }
        }

    } // namespace system
} // namespace fob
