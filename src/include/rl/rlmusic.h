#ifndef RLMUSIC_H
#define RLMUSIC_H

#include <string>
#include <unordered_map>

#include "raylib.h"

#ifndef ASSET_FILES
#define ASSET_FILES std::unordered_map<std::string, const char *>
#endif

class rlMusic {
    public:
    rlMusic() {}
    ~rlMusic() { unload(); }

    bool load_assets(ASSET_FILES assets, bool auto_play_first = false) {
        bool success = false;

        for (auto it : assets) {
            if (!load(it.first, it.second)) {
                success = false;
                unload(it.first);
                printf("Failed to load %s\n", it.first.c_str());
            } // keeps others loaded
        }

        if (auto_play_first && success && !music.empty()) {
            PlayMusicStream(music.begin()->second);
        }

        return success;
    }

    bool load(std::string name, std::string filepath, bool auto_play = false) {
        Music in = LoadMusicStream(filepath.c_str());
        if (!IsMusicValid(in)) return false;
        music[name] = in;
        if (auto_play) PlayMusicStream(in);
        return true;
    }

    Music *get(std::string name) { return &music.find(name)->second; }
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

    private:
    std::unordered_map<std::string, Music> music;
    Music *current;
};

#endif
