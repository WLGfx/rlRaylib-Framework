#ifndef TESTAPP_H
#define TESTAPP_H

#include "include/rlcamera.h"
#include "include/rlmodel.h"
#include "include/rlmusic.h"
#include "include/rltexture.h"

class TestApp {
    public:
        void start();
        void init();

        void update();
        void draw();

    private:
        rlCamera camera;

        rlMusic music;
        ASSET_FILES music_assets = 
        {   { "intro", "./assets/timebug.mod" },   };
        
        rlModel model;
        ASSET_FILES model_assets = 
        {   { "egypt", "./assets/egyptian/egyptian.glb" } };
};

#endif
