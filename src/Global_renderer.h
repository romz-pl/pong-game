#pragma once

#include "unique.h"
#include "SDL.h"

namespace Global
{
// Renderer for 2D drawing
extern unique< SDL_Renderer* > renderer;
}
