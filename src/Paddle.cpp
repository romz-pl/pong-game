#include "Paddle.h"

#include "Global_renderer.h"
#include "Global_window.h"

void Paddle::Initialize()
{
    mDir = 0;
    mx = 10.0f;
    my = 0.5 * Global::GetWindowH();
}

//
// Update paddle position based on direction
//
void Paddle::Update( float deltaTime )
{
    if (mDir != 0)
    {
        my += mDir * 300.0f * deltaTime;
        // Make sure paddle doesn't move off screen!
        if (my < (paddleH/2.0f + thickness))
        {
            my = paddleH/2.0f + thickness;
        }
        else if (my > (Global::GetWindowH() - paddleH/2.0f - thickness))
        {
            my = Global::GetWindowH() - paddleH/2.0f - thickness;
        }
    }
}

//
// Draw paddle
//
void Paddle::GenerateOutput()
{
    SDL_Rect rect{
        static_cast<int>(mx),
                static_cast<int>(my - paddleH/2),
                thickness,
                static_cast<int>(paddleH)
    };
    SDL_RenderFillRect(Global::renderer.get(), &rect);
}
