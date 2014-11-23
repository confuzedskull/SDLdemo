#include <SDL.h>
#include <iostream>
#include <string>
#include <map>

SDL_Window* main_window = NULL;
SDL_Renderer* renderer = NULL;

typedef struct {int x; int y;} point;
namespace window
{
point position;
int width = 1360;
int height = 720;
void initialize()
{
    main_window = SDL_CreateWindow("My First SDL App", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, window::width, window::height, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(main_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
}
void close()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(main_window);
    main_window = NULL;
    renderer = NULL;
    SDL_Quit();
}
};

namespace cursor
{
point passive;
point left_drag;
point left_down;
point left_up;
point right_drag;
point right_down;
point right_up;
bool left_clicked;
bool right_clicked;
bool left_dragging;
bool right_dragging;
};

void action_placeholder(){};

namespace game
{
    SDL_Rect object;
void initialize()
{
    object.x=0;
    object.y=0;
    object.w=64;
    object.h=64;
}
void render()
{
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderFillRect(renderer,&object);
    SDL_RenderPresent(renderer);
}
void update()
{
    /*object.x=cursor::left_down.x;
    object.y=cursor::left_down.y;*/
}
};

namespace controls
{
std::map<char,void (*)()> key_bindings;
std::map<std::string,void (*)()> special_bindings;
void move_up()
{
    game::object.y--;
}
void move_down()
{
    game::object.y++;
}
void move_left()
{
    game::object.x--;
}
void move_right()
{
    game::object.x++;
}
void initialize()
{
    key_bindings['w']=move_up;
    key_bindings['a']=move_left;
    key_bindings['s']=move_down;
    key_bindings['d']=move_right;
    special_bindings["up"]=move_up;
    special_bindings["left"]=move_left;
    special_bindings["down"]=move_down;
    special_bindings["right"]=move_right;
}

void process_keys()
{
    const Uint8* key_states = SDL_GetKeyboardState(NULL);
    if(key_states[SDL_SCANCODE_UP])
        special_bindings["up"]();
    if(key_states[SDL_SCANCODE_DOWN])
        special_bindings["down"]();
    if(key_states[SDL_SCANCODE_LEFT])
        special_bindings["left"]();
    if(key_states[SDL_SCANCODE_RIGHT])
        special_bindings["right"]();
    if(key_states[SDL_SCANCODE_RETURN])
        special_bindings["enter"]();
    if(key_states[SDL_SCANCODE_INSERT])
        special_bindings["insert"]();
    if(key_states[SDL_SCANCODE_DELETE])
        special_bindings["delete"]();
    for(auto kb:key_bindings)
    {
        if(key_states[SDL_GetScancodeFromKey(kb.first)])
            kb.second();
    }
}

void process_mouse()
{
    SDL_Event mouse_event;
    SDL_PollEvent(&mouse_event);
    if(mouse_event.button.type == SDL_MOUSEBUTTONDOWN)
    {
        if(mouse_event.button.button == SDL_BUTTON_LEFT)
        {
            cursor::left_clicked=true;
            cursor::left_down.x=mouse_event.button.x;
            cursor::left_down.y=mouse_event.button.y;
        }
        if(mouse_event.button.button == SDL_BUTTON_RIGHT)
        {
            cursor::right_clicked=true;
            cursor::right_down.x=mouse_event.button.x;
            cursor::right_down.y=mouse_event.button.y;
        }
    }
    if(mouse_event.button.type == SDL_MOUSEBUTTONUP)
    {
        if(mouse_event.button.button == SDL_BUTTON_LEFT)
        {
            cursor::left_clicked=false;
            cursor::left_up.x=mouse_event.button.x;
            cursor::left_up.y=mouse_event.button.y;
        }
        if(mouse_event.button.button == SDL_BUTTON_RIGHT)
        {
            cursor::right_clicked=false;
            cursor::right_up.x=mouse_event.button.x;
            cursor::right_up.y=mouse_event.button.y;
        }
    }
    if(mouse_event.type == SDL_MOUSEMOTION)
    {
        cursor::passive.x=mouse_event.motion.x;
        cursor::passive.y=mouse_event.motion.y;
        if(cursor::left_clicked)
        {
            cursor::left_dragging=true;
            cursor::left_drag.x=mouse_event.button.x;
            cursor::left_drag.y=mouse_event.button.y;
        }
        else
            cursor::left_dragging=false;
        if(cursor::right_clicked)
        {
            cursor::right_dragging=true;
            cursor::right_drag.x=mouse_event.button.x;
            cursor::right_drag.y=mouse_event.button.y;
        }
        else
            cursor::right_dragging=false;
    }
}
}

int main(int argc, char* args[])
{
    SDL_Event main_event;
    window::initialize();
    game::initialize();
    controls::initialize();
    while(main_event.type != SDL_QUIT)
    {
        SDL_PollEvent(&main_event);
        controls::process_mouse();
        controls::process_keys();
        game::update();
        game::render();
    }
    window::close();
    return 0;
}
