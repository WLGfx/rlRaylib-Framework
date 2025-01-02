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

    /**
     * Loads music assets and sets them up for use.
     * 
     * @param assets a map of asset names to their respective file paths
     * @param auto_play_first whether to play the first asset after loading
     * @return true on success, false on failure
     */
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

    /**
     * Loads a music file from the specified filepath and associates it with the given name.
     * 
     * @param name The identifier for the music asset.
     * @param filepath The path to the music file to be loaded.
     * @param auto_play If true, the music will start playing immediately after being loaded.
     * @return true if the music was successfully loaded and is valid, false otherwise.
     */

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

    /**
     * Retrieves a pointer to the Music object associated with the given name.
     * 
     * @param name The identifier for the music asset.
     * @return A pointer to the Music object if found, otherwise nullptr.
     */

    Music *get(std::string name) { 
        return &music.find(name)->second.music; 
    }
    
    /**
     * Unloads the music associated with the given name and removes it from the registry.
     * 
     * @param name The identifier for the music asset.
     */
    void unload(std::string name) {
        auto it = music.find(name);
        if (it != music.end()) {
            UnloadMusicStream(it->second.music);
            music.erase(it);
        }
    }
    
    /**
     * Unloads all music assets and clears the music registry.
     * This function iterates over all loaded music assets, unloading each one,
     * and then clears the map that stores these assets.
     */

    void unload() {
        for (auto it : music) {
            UnloadMusicStream(it.second.music);
        }
        music.clear();
    } 

    /**
     * Starts playing the music asset with the given name.
     * 
     * @param name The identifier for the music asset.
     * @return true if the music asset was found and started successfully, false otherwise.
     */
    bool play(std::string name) {
        if (IsMusicValid(music[name].music)) {
            PlayMusicStream(music[name].music);
            music[name].playing = true;
            return true;
        }
        return false;
    }

    /**
     * Updates all playing music streams.
     * This function iterates over all assets in the registry, and if an asset is playing,
     * it calls UpdateMusicStream() on that asset.
     */
    void update() {
        for (auto asset : music) {
            if (asset.second.playing) {
                UpdateMusicStream(asset.second.music);
            }
        }
    }

};

#endif
