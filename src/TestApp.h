#ifndef TESTAPP_H
#define TESTAPP_H

#include "include/rl.h"

class TestApp {
    public:
        void start();

        void update();
        void draw();

        void cleanup();

    private:
        rlMusic music; // music handler
        rlSound sound; // sound handler
        rlTexture texture; // Texture handler
        rlFont font; // Font handler
        rlImage image; // Image handler
        rlShader shader; // Shader handler
        rlModel model; // Model handler
        rlMesh mesh; // Mesh handler
        rlMaterial material; // Material handler
        rlModelAnimation animation; // Animation handler

        Vector2 window_size = { 0, 0 };

        ASSET_FILES default_textures = {
            { "ea", "./assets/easkit.png" }
        };

        ASSET_FILES default_sounds = {
            { "coin", "./assets/resources/coin.wav" },
            { "zap", "./assets/resources/sound.wav" },
            { "target", "./assets/resources/target.ogg" },
            { "weird", "./assets/resources/weird.wav" }
        };

        ASSET_FILES default_music = {
            { "intro", "./assets/timebug.mod" },
            { "country", "./assets/resources/country.mp3" },
            { "mini", "./assets/resources/mini1111.xm" }
        };

        rlCamera camera; // Camera handler

        Transform ball1 = {
            { -1, 0, 0 },
            {0, 0, 0, 1 },
            { 1, 1, 1 }
        };
        Transform ball2 = {
            { 1, 0, 0 },
            { 0, 1, 0, 1 },
            { 1, 1, 1 }
        };
        float ball_angle2 = 0;

        Transform ea_transform = {
            { 0, 0, 1 },
            { 1, 0, 0, 1 },
            { 1, 1, 1 }
        };
        float ea_angle = 60;

        rlGui gui;
};

#endif
