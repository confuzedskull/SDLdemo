#include "game.h"
#include "window.h"
#include "cursor.h"

void game::initialize()
{
    object.x=0;
    object.y=0;
    object.w=64;
    object.h=64;
}

void game::render()
{
    SDL_SetRenderDrawColor(window::renderer, 255, 255, 255, 255);
    SDL_RenderClear(window::renderer);
    SDL_SetRenderDrawColor(window::renderer, 0, 0, 0, 255);
    SDL_RenderFillRect(window::renderer,&object);
    SDL_RenderPresent(window::renderer);
}

void game::update()
{
    object.x=cursor::left_down.x;
    object.y=cursor::left_down.y;
}
