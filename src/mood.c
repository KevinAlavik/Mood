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
        .args = NULL,
        .num_args = 3
    };

    window_event_t doge_sprite = {
        .code = 1,
        .args = NULL, 
        .num_args = 3
    };

    background_black.args = (int*)malloc(sizeof(int) * background_black.num_args);
    doge_sprite.args = (int*)malloc(sizeof(int) * doge_sprite.num_args);

    if (background_black.args == NULL || doge_sprite.args == NULL) {
        mood_log(stderr, "Error", "Memory allocation for event arguments failed");
        exit(EXIT_FAILURE);
    }

    background_black.args[0] = 0;
    background_black.args[1] = 0;
    background_black.args[2] = 0;

    doge_sprite.args[0] = (int)strdup("./assets/doge.jpg");
    doge_sprite.args[1] = 0;
    doge_sprite.args[2] = 0;

    update_window(window, &background_black);
    update_window(window, &doge_sprite);
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
