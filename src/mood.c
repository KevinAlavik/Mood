#include "lib/gui.h"
#include "lib/logger.h"
#include <signal.h>

#define TARGET_FPS 60

void handle_signal(int signal) {
    if (signal == SIGINT) {
        mood_log(stdout, "Mood Event", "User terminated app. Exiting...");
        exit(EXIT_SUCCESS);
    }
}

int main() {
    signal(SIGINT, handle_signal);

    window_config_t window_config = {
        .width = 800,
        .height = 600,
        .x = SDL_WINDOWPOS_CENTERED,
        .y = SDL_WINDOWPOS_CENTERED,
        .title = "Mood - Example"
    };

    window_t window = spawn_window(&window_config);

    window_event_t set_background_color_event = {
        .code = 0,
        .args = (int[]){255, 255, 255},
        .num_args = 3
    };

    SDL_Event sdl_event;
    
    while (window.alive) {
        int start_time = SDL_GetTicks();

        update_window(&window, &set_background_color_event);

        while (SDL_PollEvent(&sdl_event)) {
            if (sdl_event.type == SDL_QUIT) {
                window.alive = 0;
            }
        }

        int elapsed_time = SDL_GetTicks() - start_time;
        int frame_delay = 1000 / TARGET_FPS;

        if (elapsed_time < frame_delay) {
            SDL_Delay(frame_delay - elapsed_time);
        }
    }

    destroy_window(&window);
    return 0;
}