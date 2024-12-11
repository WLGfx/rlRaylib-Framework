#ifndef RL_H
#define RL_H

#ifndef ASSET_FILES
#define ASSET_FILES std::unordered_map<std::string, const char *>
#endif

#include "rltexture.h"
#include "rlsound.h"
#include "rlmusic.h"
#include "rlfont.h"
#include "rlimage.h"
#include "rlshader.h"
#include "rlmodel.h"
#include "rlmesh.h"
#include "rlmaterial.h"
#include "rlmodelanimation.h"
#include "rlcamera.h"
#include "rlgui.h"

class App {
public:
    int run(int argc, char **argv);
};

#endif