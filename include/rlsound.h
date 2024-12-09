#ifndef RLSOUND_H
#define RLSOUND_H

#include <string>
#include <unordered_map>

#include "raylib.h"

#ifndef DEFAULT_FILES
#define DEFAULT_FILES std::unordered_map<std::string, const char *>
#endif

class rlSound {
    public:
    rlSound() {}
    ~rlSound() { unload(); }

    bool load(DEFAULT_FILES files) {
        for (auto it : files) {
            bool success = load(it.first, it.second);
            if (!success) return false;
        }
        return true;
    }
    bool load(const std::string name, const std::string filepath) {
        Sound in = LoadSound(filepath.c_str());
        if (!IsSoundValid(in)) return false;
        sound[name] = in;
        return true;
    }
    Sound get(const std::string name) { return sound.find(name)->second; }
    void unload(const std::string name) {
        auto it = sound.find(name);
        if (it != sound.end()) {
            UnloadSound(it->second);
            sound.erase(it);
        }
    }
    void unload() {
        for (auto &it : sound) {
            UnloadSound(it.second);
        }
        sound.clear();
    }

    void play(const std::string &name) { PlaySound(sound[name]); }
    void volume(std::string name, float volume) { SetSoundVolume(sound[name], volume); }

    private:
    std::unordered_map<std::string, Sound> sound;
};

#endif
