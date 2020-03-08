#pragma once

class Ball
{
public:
    void Initialize();

public:
    // Position of ball, X
    float mx = 0.0f;

    // Position of ball, Y
    float my = 0.0f;

    // Velocity of ball, X
    float mvx = 0.0f;

    // Velocity of ball, Y
    float mvy = 0.0f;
};
