#include "Paddle.h"

#include "Global_window.h"

void Paddle::Initialize()
{
    mDir = 0;
    mx = 10.0f;
    my = 0.5 * Global::GetWindowH();
}
