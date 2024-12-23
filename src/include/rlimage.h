#ifndef RLIMAGE_H
#define RLIMAGE_H

#include <string>
#include <unordered_map>

#include "raylib.h"

class rlImage {
    public:
    rlImage() {}
    ~rlImage() { unload(); }

    bool load(std::string name, std::string filepath) {
        Image in = LoadImage(filepath.c_str());
        if (!IsImageValid(in)) return false;
        image[name] = in;
        return true;
    }

    Image get(std::string name) { return image.find(name)->second; }
    
    void unload(std::string name) {
        auto it = image.find(name);
        if (it != image.end()) {
            UnloadImage(it->second);
            image.erase(it);
        }
    }
    void unload() {
        for (auto &it : image) {
            UnloadImage(it.second);
        }
        image.clear();
    }

    Image gen_color(std::string name, int width, int height, Color color) {
        Image out = GenImageColor(width, height, color);
        image[name] = out;
        return out;
    }

    Image gen_gradient_linear(std::string name, int width, int height, int direction, Color start, Color end) {
        Image out = GenImageGradientLinear(width, height, direction, start, end);
        image[name] = out;
        return out;
    }

    Image gen_gradient_radial(std::string name, int width, int height, float density, Color inner, Color outer) {
        Image out = GenImageGradientRadial(width, height, density, inner, outer);
        image[name] = out;
        return out;
    }

    Image gen_gradient_square(std::string name, int width, int height, float density, Color inner, Color outer) {
        Image out = GenImageGradientSquare(width, height, density, inner, outer);
        image[name] = out;
        return out;
    }

    Image gen_checked(std::string name, int width, int height, int checksX, int checksY, Color col1, Color col2) {
        Image out = GenImageChecked(width, height, checksX, checksY, col1, col2);
        image[name] = out;
        return out;
    }

    Image gen_white_noise(std::string name, int width, int height, float factor) {
        Image out = GenImageWhiteNoise(width, height, factor);
        image[name] = out;
        return out;
    }

    Image gen_perlin_noise(std::string name, int width, int height, int offsetX, int offsetY, float scale) {
        Image out = GenImagePerlinNoise(width, height, offsetX, offsetY, scale);
        image[name] = out;
        return out;
    }

    Image gen_cellular(std::string name, int width, int height, int tileSize) {
        Image out = GenImageCellular(width, height, tileSize);
        image[name] = out;
        return out;
    }

    Image gen_text(std::string name, int width, int height, const char *text) {
        Image out = GenImageText(width, height, text);
        image[name] = out;
        return out;
    }

    Image copy(std::string name, Image in) {
        Image out = ImageCopy(in);
        image[name] = out;
        return out;
    }

    Image from_image(std::string name, Image in, Rectangle rec) {
        Image out = ImageFromImage(in, rec);
        image[name] = out;
        return out;
    }

    Image from_channel(std::string name, Image in, int selectedChannel) {
        Image out = ImageFromChannel(in, selectedChannel);
        image[name] = out;
        return out;
    }

    Image gen_text(std::string name, const char *text, int fontSize, Color color) {
        Image out = ImageText(text, fontSize, color);
        image[name] = out;
        return out;
    }

    Image gen_text_ex(std::string name, Font font, const char *text, float fontSize, float spacing, Color tint) {
        Image out = ImageTextEx(font, text, fontSize, spacing, tint);
        image[name] = out;
        return out;
    }

    void format(std::string name, int newFormat) {
        ImageFormat(&image[name], newFormat);
    }

    void to_pot(std::string name, Color fill) {
        ImageToPOT(&image[name], fill);
    }

    void crop(std::string name, Rectangle rec) {
        ImageCrop(&image[name], rec);
    }

    void resize(std::string name, int newWidth, int newHeight) {
        ImageResize(&image[name], newWidth, newHeight);
    }

    void resize_canvas(std::string name, int newWidth, int newHeight, int offsetX, int offsetY, Color fill) {
        ImageResizeCanvas(&image[name], newWidth, newHeight, offsetX, offsetY, fill);
    }

    void dither(std::string name, int rBpp, int gBpp, int bBpp, int aBpp) {
        ImageDither(&image[name], rBpp, gBpp, bBpp, aBpp);
    }

    void flip_vertical(std::string name) {
        ImageFlipVertical(&image[name]);
    }

    void flip_horizontal(std::string name) {
        ImageFlipHorizontal(&image[name]);
    }

    void rotate(std::string name, int degrees) {
        ImageRotate(&image[name], degrees);
    }

    void rotate_cw(std::string name) {
        ImageRotateCW(&image[name]);
    }

    void rotate_ccw(std::string name) {
        ImageRotateCCW(&image[name]);
    }

    void color_tint(std::string name, Color color) {
        ImageColorTint(&image[name], color);
    }

    void color_invert(std::string name) {
        ImageColorInvert(&image[name]);
    }

    void color_grayscale(std::string name) {
        ImageColorGrayscale(&image[name]);
    }

    void color_contrast(std::string name, float contrast) {
        ImageColorContrast(&image[name], contrast);
    }

    void color_brightness(std::string name, int brightness) {
        ImageColorBrightness(&image[name], brightness);
    }

    void color_replace(std::string name, Color color, Color replace) {
        ImageColorReplace(&image[name], color, replace);
    }

    Rectangle get_alpha_border(std::string name, float threshold) {
        return GetImageAlphaBorder(image[name], threshold);
    }

    void clear_background(std::string name, Color color) {
        ImageClearBackground(&image[name], color);
    }

    void draw_pixel(std::string name, int posX, int posY, Color color) {
        ImageDrawPixel(&image[name], posX, posY, color);
    }

    void draw_pixel_v(std::string name, Vector2 position, Color color) {
        ImageDrawPixelV(&image[name], position, color);
    }

    void draw_line(std::string name, int startPosX, int startPosY, int endPosX, int endPosY, Color color) {
        ImageDrawLine(&image[name], startPosX, startPosY, endPosX, endPosY, color);
    }

    void draw_line_v(std::string name, Vector2 startPos, Vector2 endPos, Color color) {
        ImageDrawLineV(&image[name], startPos, endPos, color);
    }

    void draw_rectangle(std::string name, int posX, int posY, int width, int height, Color color) {
        ImageDrawRectangle(&image[name], posX, posY, width, height, color);
    }

    void draw_rectangle_v(std::string name, Vector2 position, Vector2 size, Color color) {
        ImageDrawRectangleV(&image[name], position, size, color);
    }

    void draw_rectangle_rec(std::string name, Rectangle rec, Color color) {
        ImageDrawRectangleRec(&image[name], rec, color);
    }

    void draw_rectangle_rec(std::string name, Rectangle rec, int thick, Color color) {
        ImageDrawRectangleLines(&image[name], rec, thick, color);
    }

    void draw_triangle(std::string name, Vector2 v1, Vector2 v2, Vector2 v3, Color color) {
        ImageDrawTriangle(&image[name], v1, v2, v3, color);
    }

    void draw_triangle(std::string name, Vector2 v1, Vector2 v2, Vector2 v3, Color c1, Color c2, Color c3) {
        ImageDrawTriangleEx(&image[name], v1, v2, v3, c1, c2, c3);
    }

    void draw_triangle(std::string name, Vector2 *points, int pointCount, Color color) {
        ImageDrawTriangleFan(&image[name], points, pointCount, color);
    }

    void draw_triangle_strip(std::string name, Vector2 *points, int pointCount, Color color) {
        ImageDrawTriangleStrip(&image[name], points, pointCount, color);
    }

    void draw_image(std::string dest, std::string source, Rectangle sourceRec, Rectangle destRec, Color tint) {
        ImageDraw(&image[dest], image[source], sourceRec, destRec, tint);
    }

    void draw_text(std::string name, const char *text, int posX, int posY, int fontSize, Color color) {
        ImageDrawText(&image[name], text, posX, posY, fontSize, color);
    }

    void draw_text(std::string name, const char *text, Font font, Vector2 position, float fontSize, float spacing, Color tint) {
        ImageDrawTextEx(&image[name], font, text, position, fontSize, spacing, tint);
    }

    private:
    std::unordered_map<std::string, Image> image;
};

#endif