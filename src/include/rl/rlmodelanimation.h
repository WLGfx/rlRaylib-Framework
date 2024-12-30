#ifndef RLMODELANIMATION_H
#define RLMODELANIMATION_H

#include <string>
#include <unordered_map>
#include <vector>

#include "raylib.h"

class rlModelAnimation {
    public:
    rlModelAnimation() {}
    ~rlModelAnimation() { unload(); }

    void unload(std::string name) {
        auto it = modelAnimation.find(name);
        if (it != modelAnimation.end()) {
            UnloadModelAnimation(it->second);
            modelAnimation.erase(it);
        }
    }

    void unload() {
        for (auto &it : modelAnimation) {
            UnloadModelAnimation(it.second);
        }
        modelAnimation.clear();
    }

    // loads animations and appends animation name or index if name is empty
    // returns the count
    int load(std::string name, std::string filepath) {
        int count = 0;
        ModelAnimation *animations = LoadModelAnimations(filepath.c_str(), &count);
        for (int i = 0; i < count; i++) {
            std::string anim_name = name;
            if (animations[i].name[0] != '\0') {
                anim_name += animations[i].name;
            } else {
                anim_name += std::to_string(i);}
            modelAnimation[anim_name] = animations[i];
        }
        //UnloadModelAnimations(animations, count); // deletes animations? 
        // TODO: should we do this? I don't think so. What's the pointer of this?
        return count;
    }

    // returns names with matching string
    std::vector<std::string> get_match_names(std::string name) {
        std::vector<std::string> out;
        for (auto &it : modelAnimation) {
            if (it.first.find(name) != std::string::npos) {
                out.push_back(it.first);
            }
        }
        return out;
    }

    private:
    std::unordered_map<std::string, ModelAnimation> modelAnimation;
};

#endif