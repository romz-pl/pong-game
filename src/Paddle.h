#pragma once

class Paddle
{
public:
    void Initialize();

public:
    // Direction of paddle
    int mDir = 0;

    // Position of paddle, X
    float mx = 0.0f;

    // Position of paddle, Y
    float my = 0.0f;
};
