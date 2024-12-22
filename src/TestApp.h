#ifndef TESTAPP_H
#define TESTAPP_H

#include "include/rlcamera.h"
#include "include/rlfont.h"
#include "include/rlmodel.h"
#include "include/rlmusic.h"
#include "include/rlshader.h"
#include "include/rltexture.h"
#include "include/rlights.h"

class TestApp {
    public:
        void start();
        void init();

        void update();
        void draw();

    private:
        rlFont font;

        rlCamera camera;

        rlMusic music;
        ASSET_FILES music_assets = 
        {   { "intro", "./assets/timebug.mod" },   };
        
        rlModel model;
        ASSET_FILES model_assets = 
        {   { "egypt", "./assets/egyptian/egyptian.glb" } };

        rlShader shader;
        Light light[MAX_LIGHTS] = { 
            LIGHT_POINT,
            true,
            { 0, 5, -5 },
            { 0, 0, 0 },
            RAYWHITE 
        };
};

#endif
