#include "lib/gui.h"
#include "lib/logger.h"
#include <signal.h>

void handle_signal(int signal) {
    if (signal == SIGINT) {
        mood_log(stdout, "Mood Event", "User terminated app. Exiting...");
        exit(EXIT_SUCCESS);
    }
}

void window_setup(window_t* window) {
    window_event_t background_black = {
        .code = 0,
        .args = (int[]){0, 0, 0},
        .num_args = 3
    };

    update_window(window, &background_black);
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

    window_setup(&window);

    while (window.alive) {
        window_handler(&window);
    }

    destroy_window(&window);
    return 0;
}