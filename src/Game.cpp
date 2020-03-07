#include "Game.h"

#include "Global_renderer.h"
#include "Global_window.h"

#include <iostream>

Game::Game()
    : mIsRunning( true )
{

}

//
// Initialize the game
//
bool Game::Initialize()
{
    if( !InitializeSDL() )
    {
        return false;
    }

    if( !InitializeWindow() )
    {
        return false;
    }

    if( !InitializeRenderer() )
    {
        return false;
    }

    return m_pong.Initialize();
}

//
// Initialize SDL
//
bool Game::InitializeSDL()
{
    const int sdlResult = SDL_Init( SDL_INIT_VIDEO );

    if( sdlResult != 0 )
    {
        SDL_Log( "Unable to initialize SDL: %s", SDL_GetError() );
        return false;
    }

    return true;
}

//
// Create an SDL Window
//
bool Game::InitializeWindow()
{
    Global::window.init();

    Global::window.get() = SDL_CreateWindow(
                "Game Programming in C++ (Chapter 1)", // Window title
                100,	// Top left x-coordinate of window
                100,	// Top left y-coordinate of window
                1024,	// Width of window
                768,	// Height of window
                0		// Flags (0 for no flags set)
                );

    if (!Global::window.get())
    {
        SDL_Log( "Failed to create window: %s", SDL_GetError() );
        return false;
    }

    return true;
}

//
// Create SDL renderer
//
bool Game::InitializeRenderer()
{
    Global::renderer.init();

    Global::renderer.get() = SDL_CreateRenderer(
                Global::window.get(), // Window to create renderer for
                -1,		 // Usually -1
                SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
                );

    if( !Global::renderer.get() )
    {
        SDL_Log( "Failed to create renderer: %s", SDL_GetError() );
        return false;
    }

    return true;
}

//
// Runs the game loop until the game is over
//
void Game::RunLoop()
{
    while (mIsRunning)
    {
        ProcessInput();
        UpdateGame();
        GenerateOutput();
    }
}

#include <iostream>

//
// Shutdown the game
//
void Game::ProcessInput()
{
     m_pong.ProcessInput(mIsRunning);
}

void Game::UpdateGame()
{
    m_pong.Update(mIsRunning);
}

void Game::GenerateOutput()
{
    m_pong.GenerateOutput();
}

void Game::Shutdown()
{
    SDL_DestroyRenderer( Global::renderer.get() );
    SDL_DestroyWindow( Global::window.get() );
    SDL_Quit();

    Global::renderer.destroy();
    Global::window.destroy();
}

