#ifndef __TEXTURES_H__
#define __TEXTURES_H__

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

SDL_Texture* loadTexture(SDL_Renderer *renderer, const char *filePath);

#endif // __TEXTURES_H__
