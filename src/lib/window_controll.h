#ifndef __WINDOW_CONTROLL_H__
#define __WINDOW_CONTROLL_H__

#include "gui.h"

typedef struct {
    int x;
    int y;
} point_t;

typedef struct {
    int num_points;
    point_t* points;
} shape_t;

void set_background_color(window_t* window, int r, int g, int b);
void draw_sprite(window_t* window, const char* imagePath, int x, int y, int width, int height);
void draw_pixel(window_t* window, int x, int y, Uint8 r, Uint8 g, Uint8 b);
void draw_circle(window_t* window, int x, int y, int radius, Uint8 r, Uint8 g, Uint8 b);
void draw_rectangle(window_t* window, int x, int y, int width, int height, Uint8 r, Uint8 g, Uint8 b);
void draw_triangle(window_t* window, int x1, int y1, int x2, int y2, int x3, int y3, Uint8 r, Uint8 g, Uint8 b);
void draw_custom_shape(window_t* window, shape_t shape, Uint8 r, Uint8 g, Uint8 b);
float get_current_fps();
void change_window_title(window_t* window, const char* newTitle);

#endif // __WINDOW_CONTROLL_H__
