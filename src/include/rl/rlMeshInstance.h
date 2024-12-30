#ifndef RLMESHINSTANCE_H
#define RLMESHINSTANCE_H

#include "../rl.h"
#include "rlmaterial.h"
#include <raylib.h>
#include <vector>

/*
Up until I get the shaders side working, I will have to leave
this aside for now. Mesh Instancing only works with shaders.
See docs for more...
*/

class rlMeshInstance {
    public:
        rlMeshInstance() {}
        ~rlMeshInstance() {}
    
        Mesh *mesh;
        Material *material;

        void set_mesh(Mesh *mesh) { this->mesh = mesh; }
        void set_material(Material *material) { this->material = material; }

        std::vector<Matrix> transform;

        void transform_push(Matrix *transform);
        void transform_push(Vector3 pos, Vector3 scale);
        void transform_pos_push(Vector3 pos);
        void transform_scale_push(Vector3 scale);

        void transform_set_pos(int index, Vector3 pos);
        void transform_set_scale(int index, Vector3 scale);

        void draw() { 
            if (mesh == nullptr || material == nullptr) return;
            if (transform.empty()) return;
            //DrawMeshInstanced(*mesh, *material, 
            //    &transform[0], transform.size());
            for (auto &trans : transform) {
                DrawMesh(*mesh, *material, trans);
            }
        }

        void transforms_delete() { transform.clear(); }
};

#endif