#ifndef RLMODEL_H
#define RLMODEL_H

#include <string>
#include <unordered_map>

#include "raylib.h"

#ifndef MODEL_ASSET
#define MODEL_ASSET std::unordered_map<std::string, const char *>
#endif

class rlModel {
    public:
    rlModel() {}
    ~rlModel() { unload(); }

    bool valid(std::string name) {
        return IsModelValid(model[name]);
    }

    bool load_assets(MODEL_ASSET assets) {
        bool success = false;

        for (auto it : assets) {
            model[it.first] = LoadModel(it.second);

            if (!IsModelValid(model[it.first])) {
                success = false;
                unload(it.first);
                printf("ERROR * * * Failed to load %s\n", it.second);
            }
        }

        return success;
    }

    Model load(std::string name, std::string filepath) {
        return model[name] = LoadModel(filepath.c_str());
    }

    Model load(std::string name, Mesh mesh) {
        return model[name] = LoadModelFromMesh(mesh);
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