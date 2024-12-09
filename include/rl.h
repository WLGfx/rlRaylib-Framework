#ifndef RL_H
#define RL_H

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

#ifndef DEFAULT_FILES
#define DEFAULT_FILES std::unordered_map<std::string, const char *>
#endif

class App {
public:
    int run(int argc, char **argv);
};

#endif