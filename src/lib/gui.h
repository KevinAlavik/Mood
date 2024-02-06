#ifndef __GUI_H__
#define __GUI_H__

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>

#define TARGET_FPS 60
#define NULL_INT -1

typedef struct {
    int width;
    int height;

    int x;
    int y;

    bool shouldDrawFromCenter;

    char* title;
} window_config_t;

typedef struct {
    window_config_t* config;

    SDL_Window* sdl_window;
    SDL_Renderer* renderer;

    int centerX;
    int centerY;

    bool alive;
} window_t;

window_t spawn_window(window_config_t* config);
int destroy_window(window_t* window);
void window_handle_fps_and_quit(window_t* window);

#endif // __GUI_H__
