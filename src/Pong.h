#pragma once

#include "SDL.h"
#include "Vector2d.h"
#include "Paddle.h"

class Pong
{
public:
    Pong();

    bool Initialize();
    void ProcessInput(bool& isRunning);
    void Update(bool &isRunning);
    void GenerateOutput();

private:
    // Number of ticks since start of game
    Uint32 mTicksCount;

    Paddle mPaddle;

    // Position of ball
    Vector2d mBallPos;

    // Velocity of ball
    Vector2d mBallVel;

    const int thickness = 15;
    const float paddleH = 100.0f;
};
