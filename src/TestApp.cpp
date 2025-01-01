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
                {"./assets/fnt/carbon.ttf", 100} 
            },
        { "merchant", 
                {"./assets/fnt/Merchant Copy Doublesize.ttf", 32} 
            }
        } // note extra brackets
    );

    music.load_assets({
        { "intro", "./assets/snd/timebug.mod" },
       },
       false // auto play first in list on success
    );

    // generate all 3d models being used
    model.load_assets( {
        { "egypt", 
            "./assets/3d/egypt/egyptian.glb" }
    } );
    model.load("plane",
        mesh.GenPlane("", 
        25, 25, 5, 5));
    model.load("cube",
        mesh.GenCube("", 
        1, 1, 1));
    model.load("sphere",
        mesh.GenSphere("", 
        1, 12, 12));

    shader.load_basic_lighting("lights");

    light[0] = CreateLight(LIGHT_DIRECTIONAL, 
        {-15, 15, -15}, 
        {0, 0, 0}, 
        LIGHTGRAY, 
        shader.get("lights"));
    light[1] = CreateLight(LIGHT_POINT, 
        {10, 10, 10}, 
        {0, 0, 0}, 
        DARKBLUE, 
        shader.get("lights"));
    light[2] = CreateLight(LIGHT_POINT, 
        {-1, 3, -3}, 
        {0, 0, 0}, 
        DARKGREEN,
        shader.get("lights"));
    light[0].attenuation = 0.01f;
    light[1].attenuation = 0.01f;
    light[2].attenuation = 0.01f;

    model.set_shader("egypt", 
        0, shader.get("lights"));
    model.set_shader("egypt", 
        1, shader.get("lights"));
    model.set_shader("egypt",
        2, shader.get("lights"));
    model.set_shader("egypt", 
        3, shader.get("lights"));
    model.set_shader("plane", 
        0, shader.get("lights"));
    model.set_shader("cube",
        0, shader.get("lights"));
    model.set_shader("sphere",
        0, shader.get("lights"));

    camera.pos( {0, 4, 10} );
    camera.at( {0, 1, 0} );

    music.play("intro");
}

void TestApp::update() {
    music.update();
    camera.update(CAMERA_ORBITAL);
    UpdateLightValues(shader.get("lights"), light[0]);

    ClearBackground(DARKBROWN);
    draw();
}

void TestApp::draw() {
    BeginDrawing();

        camera.begin();
        {
            DrawGrid(20, 0.5f);

            //BeginShaderMode(shader.get("lights"));
            {
                model.draw("plane",
                    {0, 0, 0},
                    1,
                    GRAY);

                model.draw("cube",
                    {-2, 1, 0},
                    1,
                    RAYWHITE);
                
                model.draw("sphere",
                    {2, 1, 0},
                    1,
                    RAYWHITE);
                
                model.draw("egypt", // name
                    {0, 1, 0},      // position
                    {0, 1, 0},      // rotation axis
                    0,              // rotation angle
                    {1, 1, 1},       // scale
                    RAYWHITE
                    );
            }
            //EndShaderMode();
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
