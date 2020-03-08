#include "Ball.h"

#include "Global_renderer.h"
#include "Global_window.h"

void Ball::Initialize()
{
    mx = 0.5f * Global::GetWindowW();
    my = 0.5f * Global::GetWindowH();

    mvx = -200.0f;
    mvy = 235.0f;
}

//
// Update ball position based on ball velocity
//
void Ball::Update( float deltaTime )
{
    mx += mvx * deltaTime;
    my += mvy * deltaTime;
}

//
// Draw ball
//
void Ball::GenerateOutput( int thickness )
{
    SDL_Rect ball{
        static_cast<int>(mx - thickness/2),
        static_cast<int>(my - thickness/2),
        thickness,
        thickness
    };

    SDL_RenderFillRect(Global::renderer.get(), &ball);
}
