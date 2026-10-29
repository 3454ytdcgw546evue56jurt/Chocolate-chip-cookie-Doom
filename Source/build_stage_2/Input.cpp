#include "SDL3\SDL.h"
#include "Input.h"
#include "Renderer.h"
#include <stdio.h>
#include <string>
#include <list>
#include <vector>

float Pointer_X = 0;
float Pointer_Y = 0;

float Prev_Pointer_X = 0;
float Prev_Pointer_Y = 0;

float Pointer_prev_X = 0;
float Pointer_prev_Y = 0;

float Pointer_X_motion = 0;
float Pointer_Y_motion = 0;

SDL_MouseButtonFlags Mouse_events;
SDL_MouseButtonFlags Mouse_events_Prev;

void Update_Input()
{
    float Get_Pointer_X;
    float Get_Pointer_Y;

    int Window_widht;
    int Window_height;

    SDL_Window *Window = (SDL_Window*) Renderer_get_window();

    SDL_GetWindowSize(Window,&Window_widht,&Window_height);
    
    Mouse_events_Prev = Mouse_events;
    Mouse_events = SDL_GetMouseState(&Get_Pointer_X, &Get_Pointer_Y);

    Pointer_X = (Get_Pointer_X/Window_widht)*Frame_widht;
    Pointer_Y = (Get_Pointer_Y/Window_height)*Frame_height;

    SDL_Event event;
    while(SDL_PollEvent(&event))
    {
        if (event.type == SDL_EVENT_QUIT) 
        {
            exit(0);
        }
    }

    Pointer_prev_X = Pointer_X;
    Pointer_prev_Y = Pointer_Y;

    Pointer_X_motion = Pointer_Y - Pointer_prev_Y;
    Pointer_Y_motion = Pointer_X - Pointer_prev_X;
}


bool Pointer_Left_pressed()
{
    return Mouse_events&&SDL_BUTTON_LEFT && !Mouse_events_Prev&&SDL_BUTTON_LEFT;
}
bool Pointer_Middle_pressed()
{
    return Mouse_events&&SDL_BUTTON_MIDDLE && !Mouse_events_Prev&&SDL_BUTTON_MIDDLE;
}
bool Pointer_Right_pressed()
{
    return Mouse_events&&SDL_BUTTON_RIGHT && !Mouse_events_Prev&&SDL_BUTTON_RIGHT;
}

bool Pointer_Left_held()
{
    return Mouse_events&&SDL_BUTTON_LEFT && Mouse_events_Prev&&SDL_BUTTON_LEFT;
}
bool Pointer_Middle_held()
{
    return Mouse_events&&SDL_BUTTON_MIDDLE && Mouse_events_Prev&&SDL_BUTTON_MIDDLE;
}
bool Pointer_Right_held()
{
    return Mouse_events&&SDL_BUTTON_RIGHT && Mouse_events_Prev&&SDL_BUTTON_RIGHT;
}

bool Pointer_Left_released()
{
    return !Mouse_events&&SDL_BUTTON_LEFT && Mouse_events_Prev&&SDL_BUTTON_LEFT;
}
bool Pointer_Middle_released()
{
    return !Mouse_events&&SDL_BUTTON_MIDDLE && Mouse_events_Prev&&SDL_BUTTON_MIDDLE;
}
bool Pointer_Right_released()
{
    return !Mouse_events&&SDL_BUTTON_RIGHT && Mouse_events_Prev&&SDL_BUTTON_RIGHT;
}