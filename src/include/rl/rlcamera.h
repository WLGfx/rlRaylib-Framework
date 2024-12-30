#ifndef RLCAMERA_H
#define RLCAMERA_H

#include "raylib.h"
#include "raymath.h"
#include "rcamera.h"

#include <string>

class rlCamera {
    public:
        Camera3D camera = {
            {0, 0, 0},
            {0, 0, 0},
            {0, 1, 0},
            45.0,
            CAMERA_PERSPECTIVE
        };

        rlCamera() {}

        std::string str_pos() {
            return "{ " + std::to_string(camera.position.x) 
            + ", " + std::to_string(camera.position.y) 
            + ", " + std::to_string(camera.position.z)
            + " }";
        }

        void begin() { BeginMode3D(camera); }
        void end() { EndMode3D(); }
        void update(int mode = CAMERA_PERSPECTIVE) { 
            UpdateCamera(&camera, mode); }

        Camera3D get() { return camera; }

        void pos( Vector3 pos ) { camera.position = pos; }
        void at( Vector3 at ) { camera.target = at; }
        void up( Vector3 up ) { camera.up = up; }
        void fov_pro( float fov, int pro ) { camera.fovy = fov; camera.projection = pro; }

        Vector3 get_forward() { return GetCameraForward(&camera); }
        Vector3 get_up() { return GetCameraUp(&camera); }
        Vector3 get_right() { return GetCameraRight(&camera); }

        void move_forward(float distance, bool miwp) { CameraMoveForward(&camera, distance, miwp); }
        void move_up(float distance) { CameraMoveUp(&camera, distance); }
        void move_right(float distance, bool miwp) { CameraMoveRight(&camera, distance, miwp); }
        void move_to_target(float delta) { CameraMoveToTarget(&camera, delta); }

        void yaw(float angle, bool rat) { CameraYaw(&camera, angle, rat); }
        void pitch(float angle, bool lock, bool rat, bool rup) { CameraPitch(&camera, angle, lock, rat, rup); }
        void roll(float angle) { CameraRoll(&camera, angle); }

        Matrix get_view() { return GetCameraViewMatrix(&camera); }
        Matrix get_projection(float aspect) { return GetCameraProjectionMatrix(&camera, aspect); }
    private:
};

#endif
