#ifndef RLSHADER_H
#define RLSHADER_H

#include <string>
#include <unordered_map>

#include "raylib.h"
#include "../rlights.h"

#define PLATFORM_DESKTOP

#if defined(PLATFORM_DESKTOP)
    #define GLSL_VERSION            330
#else   // PLATFORM_ANDROID, PLATFORM_WEB
    #define GLSL_VERSION            100
#endif

class rlShader {
    private:
    std::unordered_map<std::string, Shader> shader;
    
    public:
    rlShader() {}
    ~rlShader() { unload(); }

    bool load_basic_lighting(std::string name) {
        Shader in = LoadShader(
            TextFormat("./assets/shaders/glsl%i/lighting.vs", GLSL_VERSION),
            TextFormat("./assets/shaders/glsl%i/lighting.fs", GLSL_VERSION)
        );
        shader[name] = in;
        return IsShaderValid(in);
    }

    Shader &get(std::string name) { return shader[name]; }

    // add shader preloads file list

    bool load(std::string name, const char *vspath, const char *fspath) {
        shader[name] = LoadShader(vspath, fspath);

        if (!IsShaderValid(shader[name])){
            unload(name);
            return false;
        }

        return true;
    }
    bool load_memory(std::string name, const char *vsCode, const char *fsCode) {
        shader[name] = LoadShaderFromMemory(vsCode, fsCode);

        if (!IsShaderValid(shader[name])){
            unload(name);
            return false;
        }

        return true;
    }

    void unload(std::string name) {
        auto it = shader.find(name);
        if (it != shader.end()) {
            UnloadShader(it->second);
            shader.erase(it);
        }
    }
    
    void unload() {
        for (auto &it : shader) {
            UnloadShader(it.second);
        }
        shader.clear();
    }

    bool is_loaded(std::string name) { return shader.find(name) != shader.end(); }

    bool is_valid(std::string name) { return IsShaderValid(shader.find(name)->second); }

    int location(std::string name, const char *uniformName) {
        return GetShaderLocation(shader[name], uniformName);
    }

    int location_attrib(std::string name, const char *attribName) {
        return GetShaderLocationAttrib(shader[name], attribName);
    }

    void set_value(std::string name, int locIndex, float value, int u_type) {
        SetShaderValue(shader[name], locIndex, &value, u_type);
    }

    void set_value(std::string name, int locIndex, const void *value, int uniformType) {
        SetShaderValue(shader[name], locIndex, value, uniformType);
    }

    void set_valuev(std::string name, int locIndex, const void *value, int uniformType, int count) {
        SetShaderValueV(shader[name], locIndex, value, uniformType, count);
    }

    void set_matrix(std::string name, int locIndex, Matrix &mat) {
        SetShaderValueMatrix(shader[name], locIndex, mat);
    }

    void set_texture(std::string name, int locIndex, Texture2D &texture) {
        SetShaderValueTexture(shader[name], locIndex, texture);
    }
};

#endif