#ifndef __GUI_H__
#define __GUI_H__

#include <SDL2/SDL.h>
#include <stdbool.h>

typedef struct {
    int width;
    int height;
    int x;
    int y;
    char* title;
} window_config_t;

typedef struct {
    window_config_t* config;
    SDL_Window* sdl_window;
    bool alive;
} window_t;

typedef struct {
    int code;
    int* args;
    int num_args;
} window_event_t;

typedef struct {
    window_event_t* events;
    int size;
} window_queue_t;

window_t spawn_window(window_config_t* config);
int destroy_window(window_t* window);
void update_window(window_t* window, window_event_t* event);

#endif // __GUI_H__
