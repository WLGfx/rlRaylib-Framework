#include "TestApp.h"
#include "include/rl.h"
#include "include/rl/rlfont.h"
#include <raylib.h>

#define RAYGUI_IMPLEMENTATION
#include "include/raygui.h"

#define RLIGHTS_IMPLEMENTATION
#include "include/rlights.h"

int App::run(int argc, char **argv) {
    (void)argc; (void)argv;

    SetWindowState(FLAG_WINDOW_RESIZABLE | FLAG_MSAA_4X_HINT | FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);
    InitWindow(1280, 800, "Test App");
    
    SetTargetFPS(-1);
    
    int monitor = GetCurrentMonitor();
    Vector2 size = { (float)GetMonitorWidth(monitor), 
                     (float)GetMonitorHeight(monitor) };

    SetWindowMaxSize(size.x, size.y);
    SetWindowState(FLAG_WINDOW_RESIZABLE);// | FLAG_FULLSCREEN_MODE);
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
    font.load_assets({ 
        { "carbon", 
                {"./assets/fnt/carbon.ttf", 200} 
            },
        { "merchant", 
                {"./assets/fnt/Merchant Copy Doublesize.ttf", 32} 
            }
        } // note extra brackets
    );

    music.load_assets({
        { "intro", "./assets/snd/timebug.mod" },
       },
       true // auto play first in list on success
    );

    //model.load(model_assets);               // model
    model.load_assets(
        { "egypt", 
            "./assets/3d/egyptian/egyptian.glb" }
    );

    std::string shaderName = "lights";
    shader.load_basic_lighting(shaderName);  // shader

    model.set_shader("egypt", 0, 
        shader.get(shaderName));
    
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
        {
            DrawGrid(20, 0.5f);

            DrawPlane({ 0, 0, 0 }, 
                { 5,5 }, DARKGRAY);

            model.draw("egypt", 
                {0, 1, 0}, 
                1.0f, RAYWHITE);
        }
        camera.end();

        DrawFPS(0, 0);

        std::string cam_pos = "Camera position: " + camera.str_pos();
        font.draw("merchant", cam_pos.c_str(), 
            {0, 32}, 20, 1, RAYWHITE);
        
        font.draw("carbon", "WLGfx", 
            {200, 800}, 400, 1, RAYWHITE);

        std::string screen_size = "Screen size: " + 
            std::to_string(GetScreenWidth()) + 
            "x" + std::to_string(GetScreenHeight());
        font.draw("merchant", screen_size.c_str(), 
            {0, 64}, 20, 1, RAYWHITE);

    EndDrawing();
}
