#ifndef RLGUI_H
#define RLGUI_H

#include "raylib.h"
#include "raygui.h"

#include <string>
#include <unordered_map>
#include <vector>

class rlStyle {
    public:
         rlStyle() {}
        ~rlStyle() {}
    
        // default colors
        Color color = BLACK;
        Color border = WHITE;
        Color pressed = WHITE;
        Color hover = GRAY;

    private:
    
};

class rlBase {
    public:
        float x = 0, y = 0, w = 100, h = 30;
        const char *text = nullptr;
        bool active = false;

        int result;

        rlBase(float x, float y, float w, float h, const char *text)
            : x(x), y(y), w(w), h(h), text(text), active(false) {}
        
        virtual ~rlBase() {}

        virtual int draw() { return 0; }
        
        void set(float x, float y, float w, float h, const char *text) {
            this->x = x;
            this->y = y;
            this->w = w;
            this->h = h;
            this->text = text;
        }
        
        Rectangle offset(float x, float y) {
            return Rectangle{ this->x + x, this->y + y, this->w, this->h };
        }

        Rectangle offset(Vector2 offset) {
            return Rectangle{ this->x + offset.x, this->y + offset.y, this->w, this->h };
        }

        Rectangle scale(Vector2 offset, float scale) {
            return Rectangle{ this->x + offset.x, this->y + offset.y, this->w * scale, this->h * scale };
        }
};

class rlButton : public rlBase {
    public:
        rlButton(float x, float y, float w, float h, const char *text) 
            : rlBase(x, y, w, h, text) {}

        int draw() override {
            //printf("DRAW rlButton: %f %f %f %f %s\n", x, y, w, h, text);
            return GuiButton(Rectangle{ x, y, w, h }, text);
        }

    private:
};

class rlLabel : public virtual rlBase {
    public:
        rlLabel(float x, float y, float w, float h, const char *text) 
            : rlBase(x, y, w, h, text) {}

        int draw() override {
            return GuiLabel(Rectangle{ x, y, w, h }, text);
        }

    private:
};

class rlTextBox : public virtual rlBase {
    public:
        rlTextBox(float x, float y, float w, float h, const char *text) 
            : rlBase(x, y, w, h, text) {}

        int text_size = 12;
        bool edit_mode = false;

        int draw() override {
            return GuiTextBox({ x, y, w, h }, 
                (char *)text, text_size, edit_mode);
        }
};

class rlWindow : public virtual rlBase {
    public:
        rlWindow(float x, float y, float w, float h, const char *text)
            : rlBase(x, y, w, h, text) {}

        int draw() override {
            return GuiWindowBox(Rectangle{ x, y, w, h }, text);
        }
};

class rlGroupBox : public virtual rlBase {
    public:
        rlGroupBox(float x, float y, float w, float h, const char *text)
            : rlBase(x, y, w, h, text) {}

        int draw() override {
            return GuiGroupBox(Rectangle{ x, y, w, h }, text);
        }
};

class rlLine : public virtual rlBase {
    public:
        rlLine(float x, float y, float w, float h, const char *text)
            : rlBase(x, y, w, h, text) {}

        int draw() override {
            return GuiLine(Rectangle{ x, y, w, h }, text);
    }
};

class rlPanel : public virtual rlBase {
    public:
        rlPanel(float x, float y, float w, float h, const char *text)
            : rlBase(x, y, w, h, text) {}

        int draw() override {
            return GuiPanel(Rectangle{ x, y, w, h }, text);
        }
};

class rlTabBar : public virtual rlBase {
    public:
        std::vector<std::string> tabs;

        int active = 1;

        rlTabBar(float x, float y, float w, float h, std::vector<std::string> tabs)
            : rlBase(x, y, w, h, ""), tabs(tabs) {}

        int draw() override {
            const char **tabNames = (const char **)tabs.data();
            int tabCount = (int)tabs.size();

            return GuiTabBar(Rectangle{ x, y, w, h }, 
                tabNames, tabCount, &active);
        }
};

class rlScrollPanel : public virtual rlBase {
    public:
        Rectangle content;
        Vector2 scroll;
        Rectangle view;

        rlScrollPanel(float x, float y, float w, float h, Rectangle content, Vector2 scroll, Rectangle view)
            : rlBase(x, y, w, h, ""), content(content), scroll(scroll), view(view) {}
        
        int draw() override {
            return GuiScrollPanel(Rectangle{ x, y, w, h }, 
                text, content, &scroll, &view);
        }
};

class rlLabelButton : public virtual rlBase {
    public:
        rlLabelButton(float x, float y, float w, float h, const char *text) 
            : rlBase(x, y, w, h, text) {}

        int draw() override {
            return GuiLabelButton(Rectangle{ x, y, w, h }, text);
        }
};

class rlToggle : public virtual rlBase {
    public:
        rlToggle(float x, float y, float w, float h, const char *text, bool active) 
            : rlBase(x, y, w, h, text), active(active) {}

        bool active = false;

        int draw() override {
            return GuiToggle(Rectangle{ x, y, w, h }, text, &active);
        }
};

class rlToggleGroup : public virtual rlBase {
    public:
        int active = 1;

        rlToggleGroup(float x, float y, float w, float h, const char *text, int active)
            : rlBase(x, y, w, h, text), active(active) {}

        int draw() override {
            return GuiToggleGroup(Rectangle{ x, y, w, h }, text, &active);
        }
};

class rlToggleSlider : public virtual rlBase {
    public:
        int active = 1;

        rlToggleSlider(float x, float y, float w, float h, const char *text, int active)
            : rlBase(x, y, w, h, text), active(active) {}

        int draw() override {
            return GuiToggleSlider(Rectangle{ x, y, w, h }, text, &active);
        }
};

class rlCheckBox : public virtual rlBase {
    public:
        bool checked = false;

        rlCheckBox(float x, float y, float w, float h, const char *text, bool checked)
            : rlBase(x, y, w, h, text), checked(checked) {}

        int draw() override {
            return GuiCheckBox(Rectangle{ x, y, w, h }, text, &checked);
        }
};

class rlComboBox : public virtual rlBase {
    public:
        int active = 1;

        rlComboBox(float x, float y, float w, float h, const char *text, int active)
            : rlBase(x, y, w, h, text), active(active) {}

        int draw() override {
            return GuiComboBox(Rectangle{ x, y, w, h }, text, &active);
        }
};

class rlSpinner : public virtual rlBase {
    public:
        int value = 0;
        int min = 0;
        int max = 0;
        bool edit_mode = false;

        rlSpinner(float x, float y, float w, float h, const char *text, int value, int min, int max, bool edit_mode)
            : rlBase(x, y, w, h, text), value(value), min(min), max(max), edit_mode(edit_mode) {}

        int draw() override {
            return GuiSpinner(Rectangle{ x, y, w, h }, 
            text, &value, min, max, edit_mode);
        }
};

class rlValueBox : public virtual rlBase {
    public:
        int value = 0;
        int min = 0;
        int max = 0;
        bool edit_mode = false;

        rlValueBox(float x, float y, float w, float h, const char *text, int value, int min, int max, bool edit_mode)
            : rlBase(x, y, w, h, text), value(value), min(min), max(max), edit_mode(edit_mode) {}

        int draw() override {
            return GuiValueBox(Rectangle{ x, y, w, h }, 
                text, &value, min, max, edit_mode);
        }
};

class rlValueBoxFloat : public virtual rlBase {
    public:
        char out_value[32]="";
        float value = 0;
        bool edit_mode = false;

        rlValueBoxFloat(float x, float y, float w, float h, const char *text, float value, bool edit_mode)
            : rlBase(x, y, w, h, text), value(value), edit_mode(edit_mode) {}

        int draw() override {
            return GuiValueBoxFloat(Rectangle{ x, y, w, h }, text,
                out_value, &value, edit_mode);
        }
};

class rlSlider : public virtual rlBase {
    public:
        const char *textLeft, *textRight;
        float value = 0;
        float min = 0;
        float max = 0;

        rlSlider(float x, float y, float w, float h, const char *textLeft, const char *textRight, float value, float min, float max)
            : rlBase(x, y, w, h, textLeft), textLeft(textLeft), textRight(textRight), value(value), min(min), max(max) {}

        int draw() override {
            return GuiSlider(Rectangle{ x, y, w, h }, 
                textLeft, textRight, &value, min, max);
        }
};

class rlSliderBar : public virtual rlBase {
    public:
        const char *textLeft, *textRight;
        float value = 0;
        float min = 0;
        float max = 0;

        rlSliderBar(float x, float y, float w, float h, const char *textLeft, const char *textRight, float value, float min, float max)
            : rlBase(x, y, w, h, textLeft), textLeft(textLeft), textRight(textRight), value(value), min(min), max(max) {}

        int draw() override {
            return GuiSliderBar(Rectangle{ x, y, w, h }, 
                textLeft, textRight, &value, min, max);
        }
};

class rlProgressBar : public virtual rlBase {
    public:
        const char *textLeft, *textRight;
        float value = 0;
        float min = 0;
        float max = 0;

        rlProgressBar(float x, float y, float w, float h, const char *textLeft, const char *textRight, float value, float min, float max)
            : rlBase(x, y, w, h, textLeft), textLeft(textLeft), textRight(textRight), value(value), min(min), max(max) {}

        int draw() override {
            return GuiProgressBar(Rectangle{ x, y, w, h }, 
                textLeft, textRight, &value, min, max);
        }
};

class rlStatusBar : public virtual rlBase {
    public:
        int draw() override {
            return GuiStatusBar(Rectangle{ x, y, w, h }, text);
        }
};

class rlDummyRec : public virtual rlBase {
    public:
        int draw() override {
            return GuiDummyRec(Rectangle{ x, y, w, h }, text);
        }
};

class rlGrid : public virtual rlBase {
    public:
        float spacing;
        int sub_divs;
        Vector2 *mouse_cell;

        rlGrid(float x, float y, float w, float h, const char *text, float spacing, int sub_divs, Vector2 *mouse_cell)
            : rlBase(x, y, w, h, text), spacing(spacing), sub_divs(sub_divs), mouse_cell(mouse_cell) {}

        int draw() override {
            return GuiGrid(Rectangle{ x, y, w, h }, text, spacing, sub_divs, mouse_cell);
        }
};

class rlListView : public virtual rlBase {
    public:
        int scroll_index = 0;
        int active = 0;

        rlListView(float x, float y, float w, float h, const char *text, int scroll_index, int active)
            : rlBase(x, y, w, h, text), scroll_index(scroll_index), active(active) {}

        int draw() override {
            return GuiListView(Rectangle{ x, y, w, h }, text, &scroll_index, &active);
        }
};

class rlListViewEx : public virtual rlBase {
    public:
        const char **items;
        int item_count = 0;
        int scroll_index = 0;
        int active = 0;
        int focused = 0;

        rlListViewEx(float x, float y, float w, float h, const char **items, int item_count, int scroll_index, int active, int focused)
            : rlBase(x, y, w, h, ""), items(items), item_count(item_count), scroll_index(scroll_index), active(active), focused(focused) {}

        int draw() override {
            return GuiListViewEx(Rectangle{ x, y, w, h }, items, item_count, &scroll_index, &active, &focused);
        }
};

class rlMessageBox : public virtual rlBase {
    public:
        const char *message;
        const char *buttons;

        rlMessageBox(float x, float y, float w, float h, const char *title, const char *message, const char *buttons)
            : rlBase(x, y, w, h, title), message(message), buttons(buttons) {}

        int draw() override {
            return GuiMessageBox(Rectangle{ x, y, w, h }, text, message, buttons);
        }
};

class rlTextInputBox : public virtual rlBase {
    public:
        const char *message;
        const char *buttons;
        char *text_message;
        int text_max_size;
        bool secret_view_active;

        rlTextInputBox(float x, float y, float w, float h, const char *title, const char *message, const char *buttons, char *text_message, int text_max_size, bool secret_view_active)
            : rlBase(x, y, w, h, title), message(message), buttons(buttons), text_message(text_message), text_max_size(text_max_size), secret_view_active(secret_view_active) {}

        int draw() override {
            return GuiTextInputBox(Rectangle{ x, y, w, h }, text, message, buttons, text_message, text_max_size, &secret_view_active);
        }
};

class rlColorPicker : public virtual rlBase {
    public:
        Color color;

        rlColorPicker(float x, float y, float w, float h, const char *text, Color color = RAYWHITE)
            : rlBase(x, y, w, h, text), color(color) {}

        int draw() override {
            return GuiColorPicker(Rectangle{ x, y, w, h }, text, &color);
        }
};

class rlColorPanel : public virtual rlBase {
    public:
        Color *color;

        rlColorPanel(float x, float y, float w, float h, const char *text, Color *color)
            : rlBase(x, y, w, h, text), color(color) {}
        
        int draw() override {
            return GuiColorPanel(Rectangle{ x, y, w, h }, text, color);
        }
};

class rlColorBarAlpha : public virtual rlBase {
    public:
        float alpha;

        rlColorBarAlpha(float x, float y, float w, float h, const char *text, float alpha = 1.0f)
            : rlBase(x, y, w, h, text), alpha(alpha) {}
        
        int draw() override {
            return GuiColorBarAlpha(Rectangle{ x, y, w, h }, text, &alpha);
        }
};

class rlColorBarHue : public virtual rlBase {
    public:
        float hue;

        rlColorBarHue(float x, float y, float w, float h, const char *text, float hue = 0.0f)
            : rlBase(x, y, w, h, text), hue(hue) {}
        
        int draw() override {
            return GuiColorBarHue(Rectangle{ x, y, w, h }, text, &hue);
        }
};

class rlColorPickerHSV : public virtual rlBase {
    public:
        Vector3 *color_hsv;

        rlColorPickerHSV(float x, float y, float w, float h, const char *text, Vector3 *color_hsv)
            : rlBase(x, y, w, h, text), color_hsv(color_hsv) {}
        
        int draw() override {
            return GuiColorPickerHSV(Rectangle{ x, y, w, h }, text, color_hsv);
        }
};

class rlColorPanelHSV : public virtual rlBase {
    public:
        Vector3 *color_hsv;

        rlColorPanelHSV(float x, float y, float w, float h, const char *text, Vector3 *color_hsv)
            : rlBase(x, y, w, h, text), color_hsv(color_hsv) {}
        
        int draw() override {
            return GuiColorPanelHSV(Rectangle{ x, y, w, h }, text, color_hsv);
        }
};

class rlGui {
    public:
        rlGui() {}
        ~rlGui() {}

        float alpha = 1.0f;
        //Font font = GetFontDefault();

        std::vector<std::pair<std::string, rlBase *>> elements;

        void setAlpha(float alpha) {
            this->alpha = alpha;
        }

        void draw() {
            //GuiSetFont(font);

            for (auto &it : elements) {
                it.second->result = it.second->draw();
            }
        };

        void add(std::string name,rlBase *element) {
            elements.push_back(std::make_pair(name, element));
        }

    private:
};

#endif