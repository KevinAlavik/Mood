#include "gui.h"
#include "logger.h"
#include <stdlib.h>
#include <stdio.h>

void set_background_color(window_t* window, int r, int g, int b) {
    SDL_SetRenderDrawColor(window->renderer, r, g, b, 255);
    SDL_RenderClear(window->renderer);
    SDL_RenderPresent(window->renderer);

    DEBUG_LOG("Background color set to (%d, %d, %d)", r, g, b);
}

void draw_image(window_t* window, const char* path, int x, int y) {
    SDL_Surface* image_surface = IMG_Load(path);

    if (image_surface == NULL) {
        mood_log(stderr, "Error", "Failed to load image: %s", IMG_GetError());
        return;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(window->renderer, image_surface);
    SDL_FreeSurface(image_surface);

    if (texture == NULL) {
        mood_log(stderr, "Error", "Failed to create texture from image: %s", SDL_GetError());
        return;
    }

    SDL_Rect dest_rect = { x, y, image_surface->w, image_surface->h };
    SDL_RenderCopy(window->renderer, texture, NULL, &dest_rect);

    SDL_DestroyTexture(texture);
    SDL_RenderPresent(window->renderer);

    DEBUG_LOG("Image drawn at (%d, %d)", x, y);
}

window_t spawn_window(window_config_t* config) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        mood_log(stderr, "Error", "SDL initialization failed: %s", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    DEBUG_LOG("SDL initialized successfully");

    window_t window;

    window.sdl_window = SDL_CreateWindow(
        config->title,
        config->x,
        config->y,
        config->width,
        config->height,
        SDL_WINDOW_SHOWN
    );
    if (window.sdl_window == NULL) {
        mood_log(stderr, "Error", "SDL window creation failed: %s", SDL_GetError());
        exit(EXIT_FAILURE);
    }
    DEBUG_LOG("SDL window created successfully");

    window.renderer = SDL_CreateRenderer(sdl_window, -1, SDL_RENDERER_ACCELERATED);
    if (window.renderer == NULL) {
        mood_log(stderr, "Error", "SDL renderer creation failed: %s", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    DEBUG_LOG("SDL renderer created successfully");

    window.config = config;
    window.alive = true;

    DEBUG_LOG("Window spawned successfully");

    return window;
}

int destroy_window(window_t* window) {
    if (window->renderer != NULL) {
        SDL_DestroyRenderer(window->renderer);
    }
    if (window->sdl_window != NULL) {
        SDL_DestroyWindow(window->sdl_window);
    }
  
    SDL_Quit();

    DEBUG_LOG("Window destroyed and SDL quit successfully");

    return 0;
}

void update_window(window_t* window, window_event_t* event) {
    int num_args = event->num_args;
    int *args = event->args;

    switch(event->code) {
        case 0:

            if (num_args == 3) {
                int r = args[0];
                int g = args[1];
                int b = args[2];

                set_background_color(window, r, g, b);
            } else {
                mood_log(stderr, "Error", "Event does not have 3 arguments. set_background_color needs 3 args");
            }
            break;
        case 1:
            if (num_args == 3) {
                char* path  = (char*)args[0];
                int x       = args[1];
                int y       = args[2];

                draw_image(window, path, x, y);
            } else {
                mood_log(stderr, "Error", "Event does not have 3 arguments. draw_image needs 3 args");
            }
            break;
        default:
            mood_log(stderr, "Error", "Unsupported event code: %d", event->code);
            break;
    }
}

void window_handler(window_t* window) {
    SDL_Event sdl_event;
    int start_time = SDL_GetTicks();

    while (SDL_PollEvent(&sdl_event)) {
        if (sdl_event.type == SDL_QUIT) {
            window->alive = 0;
        }
    }

    int elapsed_time = SDL_GetTicks() - start_time;
    int frame_delay = 1000 / TARGET_FPS;

    if (elapsed_time < frame_delay) {
        SDL_Delay(frame_delay - elapsed_time);
    }
}
