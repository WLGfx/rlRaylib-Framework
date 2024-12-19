#include "TestApp.h"
#include "include/rl.h"
#include <raylib.h>

#define RAYGUI_IMPLEMENTATION
#include "include/raygui.h"

int App::run(int argc, char **argv) {
    (void)argc; (void)argv;

    SetWindowState(FLAG_WINDOW_RESIZABLE | FLAG_MSAA_4X_HINT | FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);
    InitWindow(1280, 800, "Test App");
    
    SetTargetFPS(-1);
    
    int monitor = GetCurrentMonitor();
    Vector2 size = { (float)GetMonitorWidth(monitor), 
                     (float)GetMonitorHeight(monitor) };

    SetWindowMaxSize(size.x, size.y);
    SetWindowState(FLAG_WINDOW_RESIZABLE | FLAG_FULLSCREEN_MODE);
    MaximizeWindow();

    InitAudioDevice();

    TestApp test_app;
    test_app.start();
    
    return 0;
}

void TestApp::start() {
    init();

    while (!WindowShouldClose()) {
        update();
    }
}

void TestApp::init() {
    music.load(music_assets);           // music
    music.play("intro");

    model.load(model_assets);           // model
    Model *egypt = model.get("egypt");
    
    camera.pos( {0, 4, 10} );
}

void TestApp::update() {
    music.update();
    camera.update(CAMERA_ORBITAL);

    ClearBackground(DARKBROWN);
    draw();
}

void TestApp::draw() {
    BeginDrawing();

        camera.begin();

        DrawGrid(20, 0.5f);

        model.draw("egypt", 
            {0, 0, 0}, 
            1.0f, RAYWHITE);

        camera.end();

        DrawFPS(0, 0);

        std::string cam_pos = "Camera position: " + camera.str_pos();
        DrawText(cam_pos.c_str(), 0, 32, 
            20, RAYWHITE);

    EndDrawing();
}
