#ifndef RLMUSIC_H
#define RLMUSIC_H

#include <string>
#include <unordered_map>

#include "raylib.h"

#ifndef MUSIC_ASSETS
#define MUSIC_ASSETS std::unordered_map<std::string, const char *>
#endif

class rlMusic {

    class Asset {
    public:
        Music music;
        bool playing = false;
    };

    private:
    std::unordered_map<std::string, Asset> music;

    public:
    rlMusic() {}
    ~rlMusic() { unload(); }

    bool load_assets(MUSIC_ASSETS assets, bool auto_play_first = false) {
        bool success = true;

        for (auto asset : assets) {
            if (!load(asset.first, asset.second)) {
                success = false;
            }
        }

        if (auto_play_first && success && !music.empty()) {
            PlayMusicStream(music.begin()->second.music);
            music[0].playing = true;
        }
        
        if (!success) {
            printf("ERROR * * * Failed to load music assets\n");
            unload();
        }

        return success;
    }

    bool load(std::string name, std::string filepath, bool auto_play = false) {
        music[name].music = LoadMusicStream(filepath.c_str());
        music[name].playing = false;

        if (!IsMusicValid(music[name].music)) {
            music.erase(name);
            return false;
        }

        if (auto_play) {
            PlayMusicStream(music[name].music);
            music[name].playing = true;
        }

        return true;
    }

    Music *get(std::string name) { 
        return &music.find(name)->second.music; 
    }
    /*void unload(std::string name) {
        auto it = music.find(name);
        if (it != music.end()) {
            UnloadMusicStream(it->second);
            music.erase(it);
        }
    }*/
    
    void unload() {
        for (auto it : music) {
            UnloadMusicStream(it.second.music);
        }
        music.clear();
    } 

    bool play(std::string name) {
        if (IsMusicValid(music[name].music)) {
            PlayMusicStream(music[name].music);
            music[name].playing = true;
            return true;
        }
        return false;
    }

    void update() {
        for (auto asset : music) {
            if (asset.second.playing) {
                UpdateMusicStream(asset.second.music);
            }
        }
    }

};

#endif
