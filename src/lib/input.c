#include "input.h"

key_event_t handle_input(SDL_Event event) {
    key_event_t key_event;

    if (event.type == SDL_KEYDOWN || event.type == SDL_KEYUP) {
        key_event.key_code = event.key.keysym.sym;
        const char* key_name = SDL_GetKeyName(event.key.keysym.sym);
        key_event.key = strdup(key_name);
    }

    return key_event;
}

mouse_event_t handle_mouse(SDL_Event event) {
    mouse_event_t mouse_event;

    if (event.type == SDL_MOUSEBUTTONDOWN || event.type == SDL_MOUSEBUTTONUP) {
        mouse_event.x = event.button.x;
        mouse_event.y = event.button.y;
        mouse_event.button = event.button.button;
        mouse_event.flag = 0;
    } else if (event.type == SDL_MOUSEMOTION && (event.motion.state & SDL_BUTTON(SDL_BUTTON_LEFT))) {
        mouse_event.x = event.motion.x;
        mouse_event.y = event.motion.y;
        mouse_event.button = SDL_BUTTON_LEFT;
        mouse_event.flag = 1;
    }

    return mouse_event;
}
