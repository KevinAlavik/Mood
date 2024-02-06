#include "lib/gui.h"
#include "lib/logger.h"
#include "lib/textures.h"
#include "lib/window_controll.h"
#include "lib/scenes.h"
#include <signal.h>

void handle_signal(int signal) {
    if (signal == SIGINT) {
        mood_log(stdout, "Mood Event", "User terminated app. Exiting...");
        exit(EXIT_SUCCESS);
    }
}

void window_setup(window_t* window) {
    set_background_color(window, 0, 0, 0);
}

int main(int argc, char** argv) {
    signal(SIGINT, handle_signal);
    if(argc != 2) {
        mood_log(stderr, "Mood Error", "Expected: %s <image path>", argv[0]);
        exit(1);
    }

    window_config_t window_config = {
        .width = 800,
        .height = 600,
        .x = SDL_WINDOWPOS_CENTERED,
        .y = SDL_WINDOWPOS_CENTERED,
        .shouldDrawFromCenter = true,
        .title = "Mood - Example"
    };

    window_t window = spawn_window(&window_config);

    window_setup(&window);

    while (window.alive) {
        draw_sprite(&window, argv[1], window.centerX, window.centerY, NULL_INT, NULL_INT);
        float fps = get_current_fps();
        char newTitle[100];
        snprintf(newTitle, sizeof(newTitle), "%s [FPS: %.2f]", window_config.title, fps);
        change_window_title(&window, newTitle);
        window_handle_fps_and_quit(&window);
    }

    destroy_window(&window);
    return 0;
}