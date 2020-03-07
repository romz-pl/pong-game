#pragma once

#include "unique.h"
#include "SDL.h"

namespace Global
{
// Window created by SDL
extern unique< SDL_Window* > window;

extern int GetWindowW();
extern int GetWindowH();
}
