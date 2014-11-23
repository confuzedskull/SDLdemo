#include "controls.h"
#include "cursor.h"
#include "game.h"

std::map<char,void (*)()> controls::key_bindings;
std::map<std::string,bool> controls::special_keys;

void controls::move_up()
{
    game::object.y++;
}

void controls::move_down()
{
    game::object.y--;
}

void controls::move_left()
{
    game::object.x--;
}

void controls::move_right()
{
    game::object.x++;
}

void controls::initialize()
{
    key_bindings['W']=move_up;
    key_bindings['A']=move_left;
    key_bindings['S']=move_down;
    key_bindings['D']=move_right;
}

void controls::process_keys()
{
    const Uint8* key_states = SDL_GetKeyboardState(NULL);
    if(key_states[SDL_SCANCODE_UP])
        special_keys["up"]=true;
    else if(key_states[SDL_SCANCODE_DOWN])
        special_keys["down"]=true;
    else if(key_states[SDL_SCANCODE_LEFT])
        special_keys["left"]=true;
    else if(key_states[SDL_SCANCODE_RIGHT])
        special_keys["right"]=true;
    else if(key_states[SDL_SCANCODE_RETURN])
        special_keys["enter"]=true;
    else if(key_states[SDL_SCANCODE_INSERT])
        special_keys["insert"]=true;
    else if(key_states[SDL_SCANCODE_DELETE])
        special_keys["delete"]=true;
    for(auto kb:key_bindings)
    {
        if(key_states[SDL_GetScancodeFromKey(kb.first)])
            kb.second();
    }
}

void controls::process_mouse()
{
    SDL_Event mouse_event;
    while(SDL_PollEvent(&mouse_event) != 0)
    {
        if(mouse_event.type == SDL_MOUSEBUTTONDOWN)
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
        if(mouse_event.type == SDL_MOUSEBUTTONUP)
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
                cursor::left_drag.x=mouse_event.motion.x;
                cursor::left_drag.y=mouse_event.motion.y;
            }
            else
                cursor::left_dragging=false;
            if(cursor::right_clicked)
            {
                cursor::right_dragging=true;
                cursor::right_drag.x=mouse_event.motion.x;
                cursor::right_drag.y=mouse_event.motion.y;
            }
            else
                cursor::right_dragging=false;
        }
    }
}
