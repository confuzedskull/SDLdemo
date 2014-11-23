#ifndef CURSOR_H
#define CURSOR_H
#include <SDL.h>

namespace cursor
{
extern SDL_Point passive;
extern SDL_Point left_drag;
extern SDL_Point left_down;
extern SDL_Point left_up;
extern SDL_Point right_drag;
extern SDL_Point right_down;
extern SDL_Point right_up;
extern bool left_clicked;
extern bool right_clicked;
extern bool left_dragging;
extern bool right_dragging;
};

#endif // CURSOR_H
