#pragma once

class Paddle
{
public:
    void Initialize();
    void Update( float deltaTime );
    void GenerateOutput();

public:
    // Direction of paddle
    int mDir = 0;

    // Position of paddle, X
    float mx = 0.0f;

    // Position of paddle, Y
    float my = 0.0f;

    const int thickness = 15;
    const float paddleH = 100.0f;
};
