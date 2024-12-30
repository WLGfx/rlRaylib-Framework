#include "rlMeshInstance.h"
#include <raylib.h>

//#include <glm/glm.hpp>
//#include <glm/ext.hpp>

//#include "FastNoiseLite.h"

/*
Matrix = { // Column major, OpenGL style, right-handed
    { m0, m4, m8, m12 },  // Matrix first row (4 components)
    { m1, m5, m9, m13 },  // Matrix second row (4 components)
    { m2, m6, m10, m14 }, // Matrix third row (4 components)
    { m3, m7, m11, m15 } // Matrix fourth row (4 components)
};

Identity matrix = {
    { 1, 0, 0, 0 },
    { 0, 1, 0, 0 },
    { 0, 0, 1, 0 },
    { 0, 0, 0, 1 }
};

Translate matrix = {
    { 1, 0, 0, tx },
    { 0, 1, 0, ty },
    { 0, 0, 1, tz },
    { 0, 0, 0, 1 }
};

Scale matrix = {
    { sx, 0, 0, 0 },
    { 0, sy, 0, 0 },
    { 0, 0, sz, 0 },
    { 0, 0, 0, 1 }
};

Rotate matrix = {
    { cos(angle), -sin(angle), 0, 0 },
    { sin(angle), cos(angle), 0, 0 },
    { 0, 0, 1, 0 },
    { 0, 0, 0, 1 }
};
*/

void rlMeshInstance::transform_push(Matrix *trans) {
    transform.push_back( {
        trans->m0, trans->m4, trans->m8, trans->m12 ,
        trans->m1, trans->m5, trans->m9, trans->m13 ,
        trans->m2, trans->m6, trans->m10, trans->m14 ,
        trans->m3, trans->m7, trans->m11, trans->m15 } 
    );
}

void rlMeshInstance::transform_push(Vector3 pos, Vector3 scale) {
    transform.push_back({
         scale.x, 0, 0, pos.x ,
         0, scale.y, 0, pos.y ,
         0, 0, scale.z, pos.z ,
         0, 0, 0, 1} );
}

void rlMeshInstance::transform_pos_push(Vector3 pos) {
    transform.push_back( {
         1, 0, 0, pos.x ,
         0, 1, 0, pos.y ,
         0, 0, 1, pos.z ,
         0, 0, 0, 1 } );
}

void rlMeshInstance::transform_scale_push(Vector3 scale) {
    transform.push_back( {
         scale.x, 0, 0, 0 ,
         0, scale.y, 0, 0 ,
         0, 0, scale.z, 0 ,
         0, 0, 0, 1 } );
}

void rlMeshInstance::transform_set_pos(int index, Vector3 pos) {
    Matrix *trans = &transform[index];
    trans->m12 = pos.x;
    trans->m13 = pos.y;
    trans->m14 = pos.z;
}

void rlMeshInstance::transform_set_scale(int index, Vector3 scale) {
    Matrix *trans = &transform[index];
    trans->m0 = scale.x;
    trans->m5 = scale.y;
    trans->m10 = scale.z;
}
