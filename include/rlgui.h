#ifndef RLGUI_H
#define RLGUI_H

//#include "raygui.h"
#include "raylib.h"
#include <string>

class rlStyle {
    public:
        rlStyle() {}
        ~rlStyle() {}
    
        Color color = BLACK;
        Color border = WHITE;
        Color pressed = WHITE;
        Color hover = GRAY;

    private:
    
};

class rlButton : public rlStyle {
    public:
        rlButton() {}
        rlButton(
                Vector2 pos = { 0, 0 },
                Vector2 dim = { 100, 30 },
                const char *print = "Button" ) 
                : pos(pos), size(dim), text(print) {}
        ~rlButton() {}

        Vector2 pos = { 0, 0 };
        Vector2 size = { 100, 30 };
        const char *text = "Button";

        void draw(bool flag_hover, bool flag_pressed) {
            if (flag_hover) {
                DrawRectangle( pos.x, pos.y, size.x, size.y, hover );
            } else if (flag_pressed) {
                DrawRectangle( pos.x, pos.y, size.x, size.y, pressed );
            } else {
                DrawRectangle( pos.x, pos.y, size.x, size.y, color );
            }
            DrawRectangle( pos.x, pos.y, size.x, size.y, color );
            DrawText(text, 
                pos.x + size.x / 2 - (float)MeasureText(text, 20) / 2, 
                pos.y + size.y / 2 - 10, 20, 
                border );
        };
};

class rlGui {
    public:
        rlGui() {}
        ~rlGui() {}



        void draw_button(rlButton button, bool flag_hover, bool flag_pressed) {
            button.draw(flag_hover, flag_pressed);
        }

    private:


};

#endif