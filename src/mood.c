#include "lib/gui.h"
#include "lib/logger.h"
#include "lib/textures.h"
#include "lib/window_controll.h"
#include "lib/scenes.h"
#include "lib/input.h"

#include <signal.h>
#include <stdlib.h> 
#include <time.h>

void handle_signal(int signal) {
    if (signal == SIGINT) {
        mood_log(stdout, "Mood Event", "User terminated app. Exiting...");
        exit(EXIT_SUCCESS);
    }
}

void window_setup(window_t* window) {
    set_background_color(window, 0, 0, 0);
}

void update(window_t* window) {
    SDL_Event sdl_event;

    while (SDL_PollEvent(&sdl_event)) {
        mouse_event_t mouse_event = handle_mouse(sdl_event);
        if (mouse_event.flag == 0 && (sdl_event.type == SDL_MOUSEBUTTONDOWN || sdl_event.type == SDL_MOUSEMOTION) && mouse_event.button == SDL_BUTTON_LEFT) {
            draw_rectangle(window, mouse_event.x, mouse_event.y, 10, 10, 255, 255, 255);
            SDL_RenderPresent(window->renderer);
        }
    }
}


int main() {
    signal(SIGINT, handle_signal);
    srand(time(NULL));

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
        update(&window);

        float fps = get_current_fps();
        char newTitle[100];
        snprintf(newTitle, sizeof(newTitle), "%s [FPS: %.2f]", window_config.title, fps);
        change_window_title(&window, newTitle);
        
        handle_window_signals(&window);
    }

    destroy_window(&window);
    return 0;
}