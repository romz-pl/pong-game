#include "Global_window.h"

#include <iostream>

namespace Global
{
unique< SDL_Window* > window;

int GetWindowW()
{
    int w = 0, h = 0;
    SDL_GetWindowSize( Global::window.get(), &w, &h );
    return w;
}


int GetWindowH()
{
    int w = 0, h = 0;
    SDL_GetWindowSize( Global::window.get(), &w, &h );
    return h;
}

}
