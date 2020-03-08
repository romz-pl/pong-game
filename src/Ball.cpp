#include "Ball.h"

#include "Global_window.h"

void Ball::Initialize()
{
    mx = 0.5f * Global::GetWindowW();
    my = 0.5f * Global::GetWindowH();

    mvx = -200.0f;
    mvy = 235.0f;
}
