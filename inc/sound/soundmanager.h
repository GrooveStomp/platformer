#ifndef FOB_SOUND_MANAGER_H
#define FOB_SOUND_MANAGER_H

#include <map>
#include <SDL_mixer.h>
#include <string>
#include <vector>

namespace fob {
    namespace system {

struct SoundState
{
    SoundState();
    SoundState(const char *path);
    ~SoundState();
    Mix_Chunk *data;
};

namespace SoundUtils
{
    void Play(const SoundState &sound);
    void Loop(const SoundState &sound);
    void Stop(const SoundState &sound);
    void Pause(const SoundState &sound);
    void Unpause(const SoundState &sound);
}

        class SoundObject {
            public:
                SoundObject(std::string name);
                ~SoundObject();
                void AddReference(unsigned int id);
                void RemoveReference(unsigned int id);
                bool HasReference(unsigned int id);
                bool HasReferences();
                int References();
                std::string Name();
                Mix_Chunk* Data();

            private:
                Mix_Chunk * _sound;
                std::string _name;
                std::vector<unsigned int> _references;
        };

        class SoundManager {
            public:
                static SoundManager& Instance();
                bool Init(std::string cfg_name);
                bool Load(std::string path, unsigned int id);
                bool LoadFromCfg(std::string path, unsigned int id);
                bool Play(std::string path);
                bool Loop(std::string path, int loops=0);
                bool Stop(std::string path);
                void Pause(std::string path);
                void UnPause(std::string path);
                void RemoveReferences(unsigned int id);

            private:
                int IndexOf(std::string path);
                SoundManager();
                ~SoundManager();
                unsigned int _rate;
                unsigned int _format;
                unsigned int _num_channels;
                unsigned int _chunk_size;
                std::vector<SoundObject*> _sounds;
                std::map<std::string, int> _channels;
        };

    } // namespace system
} // namespace fob

#endif
