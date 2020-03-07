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

    bool InitializeWindow();
    bool InitializeRenderer();
    bool InitializeSDL();

private:
    // Game should continue to run
    bool mIsRunning;

    Pong m_pong;
};

