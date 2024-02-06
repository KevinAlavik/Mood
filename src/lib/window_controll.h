#ifndef __WINDOW_CONTROLL_H__
#define __WINDOW_CONTROLL_H__

#include "gui.h"

void set_background_color(window_t* window, int r, int g, int b);
void draw_sprite(window_t* window, const char* imagePath, int x, int y, int width, int height);
float get_current_fps();
void change_window_title(window_t* window, const char* newTitle);

#endif // __WINDOW_CONTROLL_H__
