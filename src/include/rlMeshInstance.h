#ifndef RLMESHINSTANCE_H
#define RLMESHINSTANCE_H

#include "rl.h"
#include "rlmaterial.h"
#include <raylib.h>
#include <vector>

class rlMeshInstance {
    public:
        rlMeshInstance() {}
        ~rlMeshInstance() {}
    
        Mesh *mesh = nullptr;
        Material *material = nullptr;

        std::vector<Matrix> transform;

        void transform_push(Vector3 pos, Vector3 scale);
        void transform_pos_push(Vector3 pos);
        void transform_scale_push(Vector3 scale);

        void transform_set_pos(int index, Vector3 pos);
        void transform_set_scale(int index, Vector3 scale);

        void draw();

        void transforms_delete() { transform.clear(); }
};

#endif