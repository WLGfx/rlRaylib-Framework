#ifndef RLSHADER_H
#define RLSHADER_H

#include <string>
#include <unordered_map>

#include "raylib.h"

class rlShader {
    public:
    rlShader() {}
    ~rlShader() { unload(); }

    // add shader preloads file list

    bool load(std::string name, const char *vspath, const char *fspath) {
        Shader in = LoadShader(vspath, fspath);
        if (!IsShaderValid(in)) return false;
        shader[name] = in;
        return true;
    }
    bool load_memory(std::string name, const char *vsCode, const char *fsCode) {
        Shader in = LoadShaderFromMemory(vsCode, fsCode);
        if (!IsShaderValid(in)) return false;
        shader[name] = in;
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

    private:
    std::unordered_map<std::string, Shader> shader;
};

#endif