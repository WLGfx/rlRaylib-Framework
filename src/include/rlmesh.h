#ifndef RLMESH_H
#define RLMESH_H

#include <string>
#include <unordered_map>

#include "raylib.h"

class rlMesh {
    public:
    rlMesh() {}
    ~rlMesh() { unload(); }

    void unload() {
        for (auto &it : mesh) {
            UnloadMesh(it.second);
        }
        mesh.clear();
    }

    void unload(std::string name) {
        auto it = mesh.find(name);
        if (it != mesh.end()) {
            UnloadMesh(it->second);
            mesh.erase(it);
        }
    }

    Mesh GenPoly(std::string name, int sides, float radius) {
        Mesh poly = GenMeshPoly(sides, radius);
        if (!name.empty()) mesh[name] = poly;
        return poly;
    }

    Mesh GenPlane(std::string name, float width, float length, int resX, int resZ) {
        Mesh plane = GenMeshPlane(width, length, resX, resZ);
        if (!name.empty()) mesh[name] = plane;
        return plane;
    }

    Mesh GenCube(std::string name, float width, float height, float length) {
        Mesh cube = GenMeshCube(width, height, length);
        if (!name.empty()) mesh[name] = cube;
        return cube;
    }

    Mesh GenSphere(std::string name, float radius, int rings, int slices) {
        Mesh sphere = GenMeshSphere(radius, rings, slices);
        if (!name.empty()) mesh[name] = sphere;
        return sphere;
    }

    Mesh GenHemiSphere(std::string name, float radius, int rings, int slices) {
        Mesh sphere = GenMeshHemiSphere(radius, rings, slices);
        if (!name.empty()) mesh[name] = sphere;
        return sphere;
    }

    Mesh GenCylinder(std::string name, float radius, float height, int slices) {
        Mesh cylinder = GenMeshCylinder(radius, height, slices);
        if (!name.empty()) mesh[name] = cylinder;
        return cylinder;
    }

    Mesh GenCone(std::string name, float radius, float height, int slices) {
        Mesh cone = GenMeshCone(radius, height, slices);
        if (!name.empty()) mesh[name] = cone;
        return cone;
    }

    Mesh GenTorus(std::string name, float radius, float size, int radSeg, int sides) {
        Mesh torus = GenMeshTorus(radius, size, radSeg, sides);
        if (!name.empty()) mesh[name] = torus;
        return torus;
    }

    Mesh GenKnot(std::string name, float radius, float size, int radSeg, int sides) {
        Mesh knot = GenMeshKnot(radius, size, radSeg, sides);
        if (!name.empty()) mesh[name] = knot;
        return knot;
    }

    Mesh GenHeightmap(std::string name, Image heightmap, Vector3 size) {
        Mesh map = GenMeshHeightmap(heightmap, size);
        if (!name.empty()) mesh[name] = map;
        return map;
    }

    Mesh GenCubicmap(std::string name, Image cubicmap, Vector3 cubeSize) {
        Mesh map = GenMeshCubicmap(cubicmap, cubeSize);
        if (!name.empty()) mesh[name] = map;
        return map;
    }

    Mesh get(std::string name) { return mesh.find(name)->second; }
    
    bool has(std::string name) { return mesh.find(name) != mesh.end(); }

    void update(std::string name, int ind, const void *data, int dataSize, int offset) {
        UpdateMeshBuffer(mesh[name], ind, data, dataSize, offset);
    }

    void draw(std::string name, Material mat, Matrix transform) {
        DrawMesh(mesh[name], mat, transform);
    }

    // this is going to be my favourite function
    void draw(std::string name, Material mat, const Matrix *transforms, int instances) {
        DrawMeshInstanced(mesh[name], mat, transforms, instances);
    }

    BoundingBox bounding_box(std::string name) {
        return GetMeshBoundingBox(mesh[name]);
    }

    void gen_tangents(std::string name) {
        GenMeshTangents(&mesh[name]);
    }

    bool export_mesh(std::string name, const char *fileName) {
        return ExportMesh(mesh[name], fileName);
    }

    bool export_code(std::string name, const char *fileName) {
        return ExportMeshAsCode(mesh[name], fileName);
    }

    private:
    std::unordered_map<std::string, Mesh> mesh;
};

#endif