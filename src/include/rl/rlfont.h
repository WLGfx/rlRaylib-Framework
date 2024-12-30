#ifndef RLFONT_H
#define RLFONT_H

#include <cmath>
#include <string>
#include <unordered_map>

#include "raylib.h"

#define FONT_ASSETS std::unordered_map<std::string, Asset>

class rlFont {
    private:
    std::unordered_map<std::string, Font> font;

    public:
    class Asset {
        public:
        std::string fname;
        int fsize;
    };

    rlFont() {}
    ~rlFont() { unload(); }

    Font load_default(std::string name) {
        return font[name] = GetFontDefault();
    }

    bool load_assets(FONT_ASSETS assets) {
        bool success = true;

        if (assets.empty()) {
            font["default"] = GetFontDefault();
        }

        for (auto it : assets) {
            Font in = LoadFontEx(it.second.fname.c_str(), it.second.fsize, NULL, 0);
            if (!IsFontValid(in)) {
                success = false;
                unload(it.first);
                printf("Failed to load %s\n", it.second.fname.c_str());
            }
        }

        if (!success) {
            unload();
            puts("Failed to load font assets");
        }
        
        return success;
    }

    Font load(std::string name, std::string filepath) {
        Font in = LoadFont(filepath.c_str());
        if (!IsFontValid(in)) return {};
        font[name] = in;
        return in;
    }
    Font load(std::string name, const char *fname, int fsize, 
            int *codepoints = NULL, int codepointCount = 0) {
        Font in = LoadFontEx(fname, fsize, codepoints, codepointCount);
        if (!IsFontValid(in)) return {};
        font[name] = in;
        return in;
    }

    // allows for multiple uses of a single font file in memory
    // *file_type ie = ".ttf"
    Font load(std::string name, const char *file_type, const unsigned char *data, int data_size, 
            int font_size, int *code_points = NULL, int codepointCount = 0) {
        Font in = LoadFontFromMemory(file_type, data, data_size, 
            font_size, code_points, codepointCount);
        if (!IsFontValid(in)) return {};
        font[name] = in;
        return in;
    }
    /*Font load(std::string name, Image image, Color key, int firstChar) {
        Font in = LoadFontFromImage(image, key, firstChar);
        if (!IsFontValid(in)) return {};
        font[name] = in;
        return in;
    }
    Font load(std::string name, char *ftype, unsigned char *fdata, 
            int dsize, int fsize, 
            int *codepoints, int codepointCount) {
        Font in = LoadFontFromMemory(ftype, fdata, dsize, fsize, codepoints, codepointCount);
        if (!IsFontValid(in)) return {};
        font[name] = in;
        return in;
    }*/
    Font get(std::string name) { return font.find(name)->second; }
    void unload(std::string name) {
        auto it = font.find(name);
        if (it != font.end()) {
            UnloadFont(it->second);
            font.erase(it);
        }
    }
    void unload() {
        for (auto &it : font) {
            UnloadFont(it.second);
        }
        font.clear();
    }

    bool valid(std::string name) {
        return font.find(name) != font.end();
    }

    bool export_code(std::string name, std::string filepath) {
        return ExportFontAsCode(font[name], filepath.c_str());
    }

    bool export_code(std::string name, char *fname) {
        return ExportFontAsCode(font[name], fname);
    }

    void draw(std::string name, const char *text, Vector2 pos, float fsize, 
            float spacing, Color tint) {
        DrawTextEx(font[name], text, pos, fsize, spacing, tint);
    }

    void draw(std::string name, char *text, Vector2 pos, float fsize, 
            float spacing, Color tint, Vector2 origin, float rotation) {
        DrawTextPro(font[name], text, pos, origin, rotation, fsize, spacing, tint);
    }

    void draw(std::string name, int codepoint, Vector2 pos, float fsize, Color tint) {
        DrawTextCodepoint(font[name], codepoint, pos, fsize, tint);
    }

    void draw(std::string name, int *codepoints, int codepointCount, Vector2 pos, float fsize, float spacing, Color tint) {
        DrawTextCodepoints(font[name], codepoints, codepointCount, pos, fsize, spacing, tint);
    }

    Vector2 measure(std::string name, char *text, float fontSize, float spacing) {
        Vector2 out = MeasureTextEx(font[name], text, fontSize, spacing);
        return out;
    }

    int glyph(std::string name, int codepoint) {
        return GetGlyphIndex(font[name], codepoint);
    }

    GlyphInfo glyph_info(std::string name, int codepoint) {
        return GetGlyphInfo(font[name], codepoint);
    }

    Rectangle glyph_atlas(std::string name, int codepoint) {
        Rectangle out = GetGlyphAtlasRec(font[name], codepoint);
        return out;
    }

   
};

#endif