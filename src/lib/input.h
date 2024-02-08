#ifndef __INPUT_H__
#define __INPUT_H__

#include "gui.h"

#include <SDL2/SDL.h>

typedef struct {
    char* key;
    int key_code;
} key_event_t;

typedef struct {
    int x;
    int y;
    int button;
    int flag;
} mouse_event_t;

key_event_t handle_input(SDL_Event event);
mouse_event_t handle_mouse(SDL_Event event);

#endif // __INPUT_H__