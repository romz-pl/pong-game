#pragma once

#include "SDL.h"
#include "Pong.h"


//
// Game class
//
class Game
{
public:
    Game();

    bool Initialize();

    void RunLoop();

    void Shutdown();
private:
    void ProcessInput();
    void UpdateGame();
    void GenerateOutput();

private:
    // Window created by SDL
    SDL_Window* mWindow;

    // Renderer for 2D drawing
    SDL_Renderer* mRenderer;

    // Game should continue to run
    bool mIsRunning;

    Pong m_pong;
};

