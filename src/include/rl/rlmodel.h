#ifndef RLMODEL_H
#define RLMODEL_H

#include <string>
#include <unordered_map>

#include "raylib.h"

#ifndef ASSET_FILES
#define ASSET_FILES std::unordered_map<std::string, const char *>
#endif

class rlModel {
    public:
    rlModel() {}
    ~rlModel() { unload(); }

    bool valid(std::string name) {
        return IsModelValid(model[name]);
    }

    void load(ASSET_FILES files) {
        for (auto it : files) {
            model[it.first] = LoadModel(it.second);
        }
    }

    Model load(std::string name, std::string filepath) {
        Model out = LoadModel(filepath.c_str());
        model[name] = out;
        return out;
    }

    Model load(std::string name, Mesh mesh) {
        Model out = LoadModelFromMesh(mesh);
        model[name] = out;
        return out;
    }

    Model *get( std::string name ) { return &model.find(name)->second; }

    void unload(std::string name) {
        UnloadModel(model[name]);
        model.erase(name);
    }

    void unload() {
        for (auto &it : model) {
            UnloadModel(it.second);
        }
        model.clear();
    }

    BoundingBox getBoundingBox(std::string name) {
        return GetModelBoundingBox(model[name]);
    }

    void set_mesh_material(std::string name, int mesh_id, int material_id) {
        SetModelMeshMaterial(&model[name], mesh_id, material_id);
    }

    void set_shader(std::string name, int mat, Shader shader) {
        get( name )->materials[mat].shader = shader;
    }

    void set_text(std::string name, int mat, int type, Texture2D text) {
        get( name )->materials[mat].maps[type].texture = text;
    }

    // Model drawing functions

    void draw(std::string name, Vector3 position, float scale, Color tint) {
        DrawModel(model[name], position, scale, tint);
    }

    void draw(std::string name, Vector3 position, Vector3 rotationAxis, float rotationAngle, Vector3 scale, Color tint) {
        DrawModelEx(model[name], position, rotationAxis, rotationAngle, scale, tint);
    }

    void draw_wires(std::string name, Vector3 position, float scale, Color tint) {
        DrawModelWires(model[name], position, scale, tint);
    }

    void draw_wires(std::string name, Vector3 position, Vector3 rotationAxis, float rotationAngle, Vector3 scale, Color tint) {
        DrawModelWiresEx(model[name], position, rotationAxis, rotationAngle, scale, tint);
    }

    void draw_points(std::string name, Vector3 position, float scale, Color tint) {
        DrawModelPoints(model[name], position, scale, tint);
    }

    void draw_points(std::string name, Vector3 position, Vector3 rotationAxis, float rotationAngle, Vector3 scale, Color tint) {
        DrawModelPointsEx(model[name], position, rotationAxis, rotationAngle, scale, tint);
    }

    void update_animation(std::string name, ModelAnimation anim, int frame) {
        UpdateModelAnimation(model[name], anim, frame);
    }

    void update_bones(std::string name, ModelAnimation anim, int frame) {
        UpdateModelAnimationBones(model[name], anim, frame);
    }

    bool valid_animation(std::string name, ModelAnimation anim) {
        return IsModelAnimationValid(model[name], anim);
    }

    private:
    std::unordered_map<std::string, Model> model;
};

#endif