#include "window_controll.h"
#include "logger.h"
#include "textures.h"

void set_background_color(window_t* window, int r, int g, int b) {
    SDL_SetRenderDrawColor(window->renderer, r, g, b, 255);
    SDL_RenderClear(window->renderer);
    SDL_RenderPresent(window->renderer);

    DEBUG_LOG("Background color set to (%d, %d, %d)", r, g, b);
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
        DEBUG_LOG("Drawing sprite from center.");
        destRect.x = x - destRect.w / 2;
        destRect.y = y - destRect.h / 2;
        DEBUG_LOG("Since we are drawing from center x: %d y: %d", destRect.x, destRect.y);
    } else {
        DEBUG_LOG("Drawing sprite from top left corner.");
        destRect.x = x;
        destRect.y = y;
    }

    SDL_RenderCopy(window->renderer, sprite, NULL, &destRect);
    SDL_DestroyTexture(sprite);
    DEBUG_LOG("Drew sprite at %d, %d with width %d and height %d (%s)", destRect.x, destRect.y, destRect.w, destRect.h, imagePath);
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