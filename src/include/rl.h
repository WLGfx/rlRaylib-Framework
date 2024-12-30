#ifndef RL_H
#define RL_H

#ifndef ASSET_FILES
#define ASSET_FILES std::unordered_map<std::string, const char *>
#endif

#include "rl/rltexture.h"
#include "rl/rlsound.h"
#include "rl/rlmusic.h"
#include "rl/rlfont.h"
#include "rl/rlimage.h"
#include "rl/rlshader.h"
#include "rl/rlmodel.h"
#include "rl/rlmesh.h"
#include "rl/rlmaterial.h"
#include "rl/rlmodelanimation.h"
#include "rl/rlcamera.h"
#include "rl/rlgui.h"

class App {
public:
    int run(int argc, char **argv);
};

#endif