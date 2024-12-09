#include <raylib.h>
#define RAYGUI_IMPLEMENTATION
#include "../include/raygui.h"

#define GUI_DIA_CONFIRM_IMPLEMENTATION
#include "../include/gui_dia_confirm.h"
#undef GUI_DIA_CONFIRM_IMPLEMENTATION

#define GUI_1280X800T_IMPLEMENTATION
#include "../include/gui_1280x800T.h"
#undef GUI_1280X800T_IMPLEMENTATION

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

    printf("Monitor: %d - Display: %d x %d, %d\n", monitor, (int)size.x, (int)size.y, c);

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
    model.load("cube", mesh.GenCube( "cube", 1, 1, 1));

    material.GenMaterialDefault("defmat");
    material.set_texture("defmat", MATERIAL_MAP_ALBEDO, texture.get("ea"));
    image.gen_checked("check", 8, 8, 4, 4, DARKGRAY, LIGHTGRAY);
    texture.load("check", image.get("check"));
    image.unload( "check" );

    material.GenMaterialDefault("defmat2");
    material.set_texture( "defmat2", MATERIAL_MAP_ALBEDO, texture.get("check"));

    model.set_text("rect", 0, MATERIAL_MAP_ALBEDO, texture.get("ea"));
    model.set_text("cube" , 0, MATERIAL_MAP_ALBEDO, texture.get("check"));

    sound.volume( "coin", 0.1f );

    // raygui
    GuiLoadStyle("./assets/dark.rgs");

    state = InitGuiDiaConfirm(); // fullscreen HUD layout
    screen = InitGui1280x800T(); // testing a message box

    // ah feck it, let's get started
    music.play("intro");

    while (!WindowShouldClose()) {
        update();
        SwapScreenBuffer();
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

    gui.draw_button(button1, true, true);
    int action_button = GuiButton(button2_bounds, "Button 2");
    int action_textbox = GuiTextBox(textbox_bounds, textbox_text, textbox_length, textbox_editmode);

    if (action_button == 1) { printf("Button 2 pressed\n"); } // button

    if (action_textbox == 1) { // 1 means text was entered
        printf("Textbox content: %s\n", textbox_text);
        textbox_editmode = !textbox_editmode;
    }

    if (action_textbox == 2) { // 2 means text was unfocused
        printf("Textbox content: %s\n", textbox_text);
        textbox_editmode = !textbox_editmode;
    }

    if (state.messageWindowActive) GuiDiaConfirm( &state);
}
