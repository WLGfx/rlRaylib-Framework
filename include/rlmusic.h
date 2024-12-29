#ifndef RLMUSIC_H
#define RLMUSIC_H

#include <string>
#include <unordered_map>

#include "raylib.h"

#ifndef DEFAULT_FILES
#define DEFAULT_FILES std::unordered_map<std::string, const char *>
#endif

class rlMusic {
    public:
    rlMusic() {}
    ~rlMusic() { unload(); }

    bool load(DEFAULT_FILES files) {
        for (auto it : files) {
            bool success = load(it.first, it.second);
            if (!success) return false;
        }
        return true;
    }
    bool load(std::string name, std::string filepath, bool auto_play = false) {
        Music in = LoadMusicStream(filepath.c_str());
        if (!IsMusicValid(in)) return false;
        music[name] = in;
        if (auto_play) PlayMusicStream(in);
        return true;
    }
    Music get(std::string name) { return music.find(name)->second; }
    void unload(std::string name) {
        auto it = music.find(name);
        if (it != music.end()) {
            UnloadMusicStream(it->second);
            music.erase(it);
        }
    }
    void unload() {
        for (auto &it : music) {
            UnloadMusicStream(it.second);
        }
        music.clear();
    } 

    bool play(std::string name) {
        auto it = music.find(name);
        if (it == music.end()) {
            current = nullptr;
            return false;
        }
        PlayMusicStream(it->second);
        current = &it->second;
        return true;
    }

    void update() {
        if (current == nullptr) return;
        UpdateMusicStream(*current);
    }

    void volume(std::string name, float volume) { SetMusicVolume(music[name], volume); }
    void pitch(std::string name, float pitch) { SetMusicPitch(music[name], pitch); }
    void pan(std::string name, float pan) { SetMusicPan(music[name], pan); }

    float time_length(std::string name) { return GetMusicTimeLength(music[name]); }
    float time_played(std::string name) { return GetMusicTimePlayed(music[name]); }

    private:
    std::unordered_map<std::string, Music> music;
    Music *current;
};

#endif
