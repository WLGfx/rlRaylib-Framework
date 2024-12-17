#include "include/rlgui.h"
#include <raylib.h>

#define RAYGUI_IMPLEMENTATION
#include "include/raygui.h"

#include "TestApp.h"

int App::run(int argc, char **argv) {
    (void)argc;
    (void)argv;

    SetWindowState(FLAG_WINDOW_RESIZABLE | FLAG_MSAA_4X_HINT | FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);
    InitWindow(1280, 800, "Test App");
    
    SetTargetFPS(-1);
    InitAudioDevice();

    int monitor = GetCurrentMonitor();
    Vector2 size = { (float)GetMonitorWidth(monitor), 
                     (float)GetMonitorHeight(monitor) };
    int c = GetMonitorRefreshRate(monitor);

    SetWindowMaxSize(size.x, size.y);
    SetWindowState(FLAG_WINDOW_RESIZABLE | FLAG_MSAA_4X_HINT | FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI | FLAG_FULLSCREEN_MODE);
    MaximizeWindow();

    TestApp test_app;
    test_app.start();
    
    return 0;
}

void TestApp::cleanup() {
    music.unload();
    sound.unload();
    texture.unload();
    mesh.unload();
    material.unload();
    model.unload();
}

void TestApp::start() {
    // load default textures, sounds, and music
    texture.load(default_textures);
    sound.load(default_sounds);
    music.load(default_music);

    camera.pos( { -1, 1, 5 }); // camera position

    // generate the models
    model.load("ball", mesh.GenSphere("", 1, 8, 8));
    model.load("rect", mesh.GenPlane("" , 4, 2, 2, 2));
    model.load("cube", mesh.GenCube("", 1, 1, 1));

    // setup materials
    material.GenMaterialDefault("defmat");
    material.set_texture("defmat", MATERIAL_MAP_ALBEDO, texture.get("ea"));
    
    image.gen_checked("check", 8, 8, 4, 4, DARKGRAY, LIGHTGRAY);
    texture.load("check", image.get("check"));
    image.unload( "check" ); // no need may as well clean it now

    material.GenMaterialDefault("defmat2");
    material.set_texture( "defmat2", MATERIAL_MAP_ALBEDO, texture.get("check"));

    model.set_text("rect", 0, MATERIAL_MAP_ALBEDO, texture.get("ea"));
    model.set_text("cube" , 0, MATERIAL_MAP_ALBEDO, texture.get("check"));

    sound.volume( "coin", 0.1f );

    // now init my gui
    //window_size = { (float)GetScreenWidth(), (float)GetScreenHeight() };

    GuiLoadStyle("./assets/terminal.rgs");

    gui.add("button", new rlButton(10, 10, 200, 50, "Just Click!"));
    gui.add("color", new rlColorPicker(10, 70, 200, 200, "Pick a color", GREEN));
    gui.add("progress", new rlProgressBar(10, 270, 200, 40, "Left", "Right", 0.5f, 0, 1));
    gui.add("slider", new rlSliderBar(10, 320, 200, 40, "Left", "Right", 50.0f, 0, 100));
    gui.add("slider2", new rlSlider(10, 370, 200, 40, "Left", "Right", 50.0f, 0, 100));
    
    gui.init();
    gui.offset_left_center();

    // ah feck it, let's get started
    music.play("intro");

    while (!WindowShouldClose()) {
        update();
        //SwapScreenBuffer(); // automaticly done by raylib
    }

    cleanup();
}

void TestApp::update() {
    music.update();

    BeginDrawing();
    draw();
    EndDrawing();

    ball_angle2 += GetFrameTime() * 180;
    if (ball_angle2 > 180) ball_angle2 -= 180 + 180;

    // check for button pressed and play coin sound
    if (IsKeyPressed(KEY_SPACE)) {
        sound.play("coin");
    }

    // toggle fullscreen
    if (IsKeyPressed(KEY_F)) {
        ToggleFullscreen();
    }

    // update cameras x position using sin(delta)
    float delta = GetTime() * 3.1410f;
    camera.camera.position.x = -1.0f + (sin(delta) * 1.0f);
    UpdateCamera(&camera.camera, CAMERA_PERSPECTIVE);
}

void TestApp::draw() {
    ClearBackground(DARKGRAY);
    camera.begin();
    
    Vector3 *rotation = (Vector3 *)&ball2.rotation;

    model.draw_wires("ball", ball1.translation, 1, WHITE);
    model.draw_wires("ball", ball2.translation, *rotation, ball_angle2, ball2.scale, WHITE);
    
    model.draw("rect", ea_transform.translation, (Vector3&)ea_transform.rotation, ea_angle, ea_transform.scale, RAYWHITE);
    model.draw("cube", {0, 1, 2}, 1, RAYWHITE);

    camera.end();

    // 2D and gui
    gui.draw();

    DrawFPS(0, 0);
}
