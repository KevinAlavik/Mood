#include "window_controll.h"
#include "textures.h"
#include "logger.h"

void set_background_color(window_t* window, int r, int g, int b) {
    SDL_SetRenderDrawColor(window->renderer, r, g, b, 255);
    SDL_RenderClear(window->renderer);
    SDL_RenderPresent(window->renderer);
}

void draw_sprite(window_t* window, const char* imagePath, int x, int y, int width, int height) {
    bool shouldDrawFromCenter = window->config->shouldDrawFromCenter;

    SDL_Texture* sprite = loadTexture(window->renderer, imagePath);
    if (!sprite) {
        mood_log(stderr, "Mood - Texture error", "Failed to load sprite.\n");
        return;
    }

    SDL_Rect destRect;

    if (width > 0 && height > 0) {
        destRect.w = width;
        destRect.h = height;
    } else {
        SDL_QueryTexture(sprite, NULL, NULL, &destRect.w, &destRect.h);
    }

    if (shouldDrawFromCenter) {
        destRect.x = x - destRect.w / 2;
        destRect.y = y - destRect.h / 2;
    } else {
        destRect.x = x;
        destRect.y = y;
    }

    SDL_RenderCopy(window->renderer, sprite, NULL, &destRect);
    SDL_DestroyTexture(sprite);
}

void draw_pixel(window_t* window, int x, int y, Uint8 r, Uint8 g, Uint8 b) {
    SDL_SetRenderDrawColor(window->renderer, r, g, b, 255);
    SDL_RenderDrawPoint(window->renderer, x, y);
}

void draw_circle(window_t* window, int x, int y, int radius, Uint8 r, Uint8 g, Uint8 b) {
    int cx = radius;
    int cy = 0;
    int radiusError = 1 - cx;

    while (cx >= cy) {
        draw_pixel(window, cx + x, cy + y, r, g, b);
        draw_pixel(window, cy + x, cx + y, r, g, b);
        draw_pixel(window, -cx + x, cy + y, r, g, b);
        draw_pixel(window, -cy + x, cx + y, r, g, b);
        draw_pixel(window, -cx + x, -cy + y, r, g, b);
        draw_pixel(window, -cy + x, -cx + y, r, g, b);
        draw_pixel(window, cx + x, -cy + y, r, g, b);
        draw_pixel(window, cy + x, -cx + y, r, g, b);

        cy++;
        if (radiusError < 0) {
            radiusError += 2 * cy + 1;
        } else {
            cx--;
            radiusError += 2 * (cy - cx + 1);
        }
    }
}

void draw_rectangle(window_t* window, int x, int y, int width, int height, Uint8 r, Uint8 g, Uint8 b) {
    SDL_Rect rect = { x, y, width, height };
    SDL_SetRenderDrawColor(window->renderer, r, g, b, 255);
    SDL_RenderDrawRect(window->renderer, &rect);
}

void draw_triangle(window_t* window, int x1, int y1, int x2, int y2, int x3, int y3, Uint8 r, Uint8 g, Uint8 b) {
    SDL_SetRenderDrawColor(window->renderer, r, g, b, 255);
    SDL_RenderDrawLine(window->renderer, x1, y1, x2, y2);
    SDL_RenderDrawLine(window->renderer, x2, y2, x3, y3);
    SDL_RenderDrawLine(window->renderer, x3, y3, x1, y1);
}

void draw_custom_shape(window_t* window, shape_t shape, Uint8 r, Uint8 g, Uint8 b) {
    SDL_SetRenderDrawColor(window->renderer, r, g, b, 255);
    for (int i = 0; i < shape.num_points - 1; i++) {
        SDL_RenderDrawLine(window->renderer, shape.points[i].x, shape.points[i].y, shape.points[i + 1].x, shape.points[i + 1].y);
    }
    
    SDL_RenderDrawLine(window->renderer, shape.points[shape.num_points - 1].x, shape.points[shape.num_points - 1].y, shape.points[0].x, shape.points[0].y);
}

float get_current_fps() {
    static Uint32 lastTime = 0;
    static int frames = 0;
    Uint32 current;
    float elapsed;

    current = SDL_GetTicks();
    elapsed = (current - lastTime) / 1000.0f;
    frames++;

    return frames / elapsed;
}

void change_window_title(window_t* window, const char* newTitle) {
    SDL_SetWindowTitle(window->sdl_window, newTitle);
}
