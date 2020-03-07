#pragma once

#include "SDL.h"
#include "Vector2d.h"

// Game class
class Game
{
public:
    Game();
    // Initialize the game
    bool Initialize();
    // Runs the game loop until the game is over
    void RunLoop();
    // Shutdown the game
    void Shutdown();
private:
    // Helper functions for the game loop
    void ProcessInput();
    void UpdateGame();
    void GenerateOutput();

    // Window created by SDL
    SDL_Window* mWindow;
    // Renderer for 2D drawing
    SDL_Renderer* mRenderer;
    // Number of ticks since start of game
    Uint32 mTicksCount;
    // Game should continue to run
    bool mIsRunning;

    // Pong specific
    // Direction of paddle
    int mPaddleDir;
    // Position of paddle
    Vector2d mPaddlePos;
    // Position of ball
    Vector2d mBallPos;
    // Velocity of ball
    Vector2d mBallVel;
};

