#ifndef RLTEXTURE_H
#define RLTEXTURE_H

#include <string>
#include <unordered_map>

#include "raylib.h"

#ifndef DEFAULT_FILES
#define DEFAULT_FILES std::unordered_map<std::string, const char *>
#endif

class rlTexture {
    public:
    rlTexture() {}
    ~rlTexture() { unload(); }

    // TODO: doesn't clean up after catching a failure
    bool load(std::unordered_map<std::string, const char *> &files) {
        for (auto it : files) {
            bool success = load(it.first, it.second);
            if (!success) return false;
        }
        return true;
    }

    bool load(const std::string &name, const std::string &filepath)  {
        Texture2D texture2d = LoadTexture(filepath.c_str());
        if (texture2d.id == 0) return false;
        texture[name] = texture2d;
        return true;
    }

    bool load( const std::string &name, Image image ) {
        Texture2D texture2d = LoadTextureFromImage(image);
        if (texture2d.id == 0) return false;
        texture[name] = texture2d;
        return true;
    }

    Texture2D get(const std::string &name) const {
        auto it = texture.find(name);
        if (it != texture.end()) return it->second;
        return {};
    }
    void unload(const std::string &name) {
        auto it = texture.find(name);
        if (it != texture.end()) {
            UnloadTexture(it->second);
            texture.erase(it);
        }
    }
    void unload() {
        for (auto &it : texture) {
            UnloadTexture(it.second);
        }
        texture.clear();
    }

    bool valid(const std::string &name) const {
        auto it = texture.find(name);
        if (it != texture.end()) return true;
        return false;
    }

    void gen_mips(std::string name) {
        auto t = texture.find(name);
        if (t != texture.end()) GenTextureMipmaps(&t->second);
    }

    void set_filter(std::string name, int filter) {
        auto t = texture.find(name);
        if (t != texture.end()) SetTextureFilter(t->second, filter);
    }

    void set_wrap(std::string name, int wrap) {
        auto t = texture.find(name);
        if (t != texture.end()) SetTextureWrap(t->second, wrap);
    }

    void draw(std::string name, int x, int y, Color tint) {
        auto t = texture.find(name);
        if (t != texture.end())
            DrawTexture(texture[name], x, y, tint);
    }

    void draw(std::string name, Vector2 position, Color tint) {
        auto t = texture.find(name);
        if (t != texture.end())
            DrawTextureV(texture[name], position, tint);
    }

    void draw(std::string name, Vector2 position, float rotation, float scale, Color tint) {
        auto t = texture.find(name);
        if (t != texture.end())
            DrawTextureEx(texture[name], position, rotation, scale, tint);
    }

    void draw(std::string name, Rectangle source, Vector2 position, Color tint) {
        auto t = texture.find(name);
        if (t != texture.end())
            DrawTextureRec(texture[name], source, position, tint);
    }

    void draw(std::string name, Rectangle src, Rectangle dst, Vector2 origin, float rotation, Color tint) {
        auto t = texture.find(name);
        if (t != texture.end())
            DrawTexturePro(texture[name], src, dst, origin, rotation, tint);
    }

    void npatch_draw(std::string name, NPatchInfo nPatchInfo, Rectangle dest, Vector2 origin, float rotation, Color tint) {
        auto t = texture.find(name);
        if (t != texture.end())
            DrawTextureNPatch(texture[name], nPatchInfo, dest, origin, rotation, tint);
    }

    private:
    std::unordered_map<std::string, Texture2D> texture;
};

#endif
