#ifndef RLMATERIAL_H
#define RLMATERIAL_H

#include <string>
#include <unordered_map>

#include "raylib.h"

class rlMaterial {
    public:
    rlMaterial() {}
    ~rlMaterial() { unload(); }

    void unload() {
        for (auto &it : material) {
            UnloadMaterial(it.second);
        }
        material.clear();
    }

    void unload(std::string name) {
        auto it = material.find(name);
        if (it != material.end()) {
            UnloadMaterial(it->second);
            material.erase(it);
        }
    }

    Material *get(std::string name) { return &material.find(name)->second; }

    void set_texture(std::string name, int map_type, Texture2D text) {
        SetMaterialTexture(get(name), map_type, text);
    }

    Material GenMaterial(std::string name, Shader shader) {
        // default material supports DIFFUSE, SPECULAR and NORMAL maps
        Material mat = LoadMaterialDefault();
        mat.shader = shader;
        material[name] = mat;
        return mat;
    }

    Material GenMaterialDefault(std::string name) {
        // default material supports DIFFUSE, SPECULAR and NORMAL maps
        Material mat = LoadMaterialDefault();
        material[name] = mat;
        return mat;
    }

    Material GenMaterialMaps(std::string name, 
                Texture2D diffuse, Texture2D specular, Texture2D normal) {
        Material mat = LoadMaterialDefault();
        SetMaterialTexture(&mat, MATERIAL_MAP_DIFFUSE, diffuse);
        SetMaterialTexture(&mat, MATERIAL_MAP_SPECULAR, specular);
        SetMaterialTexture(&mat, MATERIAL_MAP_NORMAL, normal);
        material[name] = mat;
        return mat;
    }

    Material GenMaterialMaps(std::string name, 
                Texture2D diffuse, Texture2D specular, Texture2D normal, 
                Texture2D emission) {
        Material mat = LoadMaterialDefault();
        SetMaterialTexture(&mat, MATERIAL_MAP_DIFFUSE, diffuse);
        SetMaterialTexture(&mat, MATERIAL_MAP_SPECULAR, specular);
        SetMaterialTexture(&mat, MATERIAL_MAP_NORMAL, normal);
        SetMaterialTexture(&mat, MATERIAL_MAP_EMISSION, emission);
        material[name] = mat;
        return mat;
    }

    Material GenMaterialMaps(std::string name, 
                Texture2D diffuse, Texture2D specular, Texture2D normal, 
                Texture2D emission, Texture2D height) {
        Material mat = LoadMaterialDefault();
        SetMaterialTexture(&mat, MATERIAL_MAP_DIFFUSE, diffuse);
        SetMaterialTexture(&mat, MATERIAL_MAP_SPECULAR, specular);
        SetMaterialTexture(&mat, MATERIAL_MAP_NORMAL, normal);
        SetMaterialTexture(&mat, MATERIAL_MAP_EMISSION, emission);
        SetMaterialTexture(&mat, MATERIAL_MAP_HEIGHT, height);
        material[name] = mat;
        return mat;
    }

    Material GenMaterialMaps(std::string name, 
                Texture2D diffuse, Texture2D specular, Texture2D normal, 
                Texture2D emission, Texture2D height, Texture2D occlusion) {
        Material mat = LoadMaterialDefault();
        SetMaterialTexture(&mat, MATERIAL_MAP_DIFFUSE, diffuse);
        SetMaterialTexture(&mat, MATERIAL_MAP_SPECULAR, specular);
        SetMaterialTexture(&mat, MATERIAL_MAP_NORMAL, normal);
        SetMaterialTexture(&mat, MATERIAL_MAP_EMISSION, emission);
        SetMaterialTexture(&mat, MATERIAL_MAP_HEIGHT, height);
        SetMaterialTexture(&mat, MATERIAL_MAP_OCCLUSION, occlusion);
        material[name] = mat;
        return mat;
    }

    Material GenMaterialMaps(std::string name, 
                Texture2D diffuse, Texture2D specular, Texture2D normal, 
                Texture2D emission, Texture2D height, Texture2D occlusion, 
                Texture2D cubemap) {
        Material mat = LoadMaterialDefault();
        SetMaterialTexture(&mat, MATERIAL_MAP_DIFFUSE, diffuse);
        SetMaterialTexture(&mat, MATERIAL_MAP_SPECULAR, specular);
        SetMaterialTexture(&mat, MATERIAL_MAP_NORMAL, normal);
        SetMaterialTexture(&mat, MATERIAL_MAP_EMISSION, emission);
        SetMaterialTexture(&mat, MATERIAL_MAP_HEIGHT, height);
        SetMaterialTexture(&mat, MATERIAL_MAP_OCCLUSION, occlusion);
        SetMaterialTexture(&mat, MATERIAL_MAP_CUBEMAP, cubemap);
        material[name] = mat;
        return mat;
    }

    Material GenMaterialMaps(std::string name, 
                Texture2D diffuse, Texture2D specular, Texture2D normal, 
                Texture2D emission, Texture2D height, Texture2D occlusion, 
                Texture2D cubemap, Texture2D irradiance, Texture2D prefilter) {
        Material mat = LoadMaterialDefault();
        SetMaterialTexture(&mat, MATERIAL_MAP_DIFFUSE, diffuse);
        SetMaterialTexture(&mat, MATERIAL_MAP_SPECULAR, specular);
        SetMaterialTexture(&mat, MATERIAL_MAP_NORMAL, normal);
        SetMaterialTexture(&mat, MATERIAL_MAP_EMISSION, emission);
        SetMaterialTexture(&mat, MATERIAL_MAP_HEIGHT, height);
        SetMaterialTexture(&mat, MATERIAL_MAP_OCCLUSION, occlusion);
        SetMaterialTexture(&mat, MATERIAL_MAP_CUBEMAP, cubemap);
        SetMaterialTexture(&mat, MATERIAL_MAP_IRRADIANCE, irradiance);
        SetMaterialTexture(&mat, MATERIAL_MAP_PREFILTER, prefilter);
        material[name] = mat;
        return mat;
    }
    
    private:
    std::unordered_map<std::string, Material> material;
};

#endif