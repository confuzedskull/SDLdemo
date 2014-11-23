#ifndef GAME_H
#define GAME_H
#include <SDL.h>

namespace game
{
    extern SDL_Rect object;
    void initialize();
    void render();
    void update();
};

#endif // GAME_H
