#ifndef TESTAPP_H
#define TESTAPP_H

#include "include/rl/rlassets.h"
#include "include/rl/rlfont.h"
#include "include/rl/rlmodel.h"
#include "include/rl/rlmusic.h"
#include "include/rl/rlshader.h"
#include "include/rl/rltexture.h"
#include "include/rl/rlcamera.h"

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
        rlModel model;
        rlShader shader;

        Light light[MAX_LIGHTS];
        /* = { 
            {
            LIGHT_POINT,
            true,
            { -5, 5, -5 },
            { 0, 0, 0 },
            RAYWHITE 
            }
        };*/
};

#endif
