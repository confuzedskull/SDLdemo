#ifndef WINDOW_H
#define WINDOW_H
#include <SDL.h>

namespace window
{
extern SDL_Window* gWindow = NULL;
extern SDL_Renderer* renderer = NULL;
extern SDL_Point position;
extern int width = 1360;
extern int height = 720;
void initialize();
void close();
};

#endif // WINDOW_H
