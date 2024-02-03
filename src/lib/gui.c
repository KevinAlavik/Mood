
#include "gui.h"
#include "logger.h"
#include <stdlib.h>
#include <stdio.h>

#ifdef DEBUG_LOGGING
#define DEBUG_LOG(...) mood_log(stdout, "Mood Debug", __VA_ARGS__)
#else
#define DEBUG_LOG(...) ((void)0)
#endif

void set_background_color(SDL_Window* window, int r, int g, int b) {
    SDL_SetRenderDrawColor(SDL_GetRenderer(window), r, g, b, 255);
    SDL_RenderClear(SDL_GetRenderer(window));
    SDL_RenderPresent(SDL_GetRenderer(window));

    DEBUG_LOG("Background color set to (%d, %d, %d)", r, g, b);
}

window_t spawn_window(window_config_t* config) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        mood_log(stderr, "Error", "SDL initialization failed: %s", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    DEBUG_LOG("SDL initialized successfully");

    SDL_Window* sdl_window = SDL_CreateWindow(
        config->title,
        config->x,
        config->y,
        config->width,
        config->height,
        SDL_WINDOW_SHOWN
    );

    if (sdl_window == NULL) {
        mood_log(stderr, "Error", "SDL window creation failed: %s", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    DEBUG_LOG("SDL window created successfully");

    window_t* window = (window_t*)malloc(sizeof(window_t));
    if (window == NULL) {
        mood_log(stderr, "Error", "Memory allocation for window_t failed");
        exit(EXIT_FAILURE);
    }

    DEBUG_LOG("Memory allocated for window_t");

    window->config = config;
    window->sdl_window = sdl_window;
    window->alive = true;

    DEBUG_LOG("Window spawned successfully");

    return *window;
}

int destroy_window(window_t* window) {
    SDL_DestroyWindow(window->sdl_window);
    SDL_Quit();

    free(window);

    DEBUG_LOG("Window destroyed and SDL quit successfully");

    return 0;
}

void update_window(window_t* window, window_event_t* event) {
    switch(event->code) {
        case 0:

            if (event->num_args == 3) {
                int r = event->args[0];
                int g = event->args[1];
                int b = event->args[2];
                
                set_background_color(window->sdl_window, r, g, b);
            } else {
                mood_log(stderr, "Error", "Event does not have 3 arguments. set_background_color needs 3 args");
            }
            break;

        default:
            mood_log(stderr, "Error", "Unsupported event code: %d", event->code);
            break;
    }
}