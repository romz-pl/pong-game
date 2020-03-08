#include "Pong.h"

#include "Global_renderer.h"
#include "Global_window.h"

Pong::Pong()
    : mTicksCount(0)   
{

}

bool Pong::Initialize()
{
    mPaddle.Initialize();
    mBall.Initialize();

    return true;
}

void Pong::ProcessInput(bool &isRunning)
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        // If we get an SDL_QUIT event, end loop
        case SDL_QUIT:
            isRunning = false;
        }
    }

    // Get state of keyboard
    const Uint8* state = SDL_GetKeyboardState(NULL);
    // If escape is pressed, also end loop
    if (state[SDL_SCANCODE_ESCAPE])
    {
        isRunning = false;
    }

    // Update paddle direction based on W/S keys
    mPaddle.mDir = 0;
    if (state[SDL_SCANCODE_W])
    {
        mPaddle.mDir -= 1;
    }
    if (state[SDL_SCANCODE_S])
    {
        mPaddle.mDir += 1;
    }
}

void Pong::Update(bool& isRunning)
{
    // Wait until 16ms has elapsed since last frame
    while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 16))
        ;

    // Delta time is the difference in ticks from last frame
    // (converted to seconds)
    float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f;

    // Clamp maximum delta time value
    if (deltaTime > 0.05f)
    {
        deltaTime = 0.05f;
    }

    // Update tick counts (for next frame)
    mTicksCount = SDL_GetTicks();

    // Update paddle position based on direction
    if (mPaddle.mDir != 0)
    {
        mPaddle.my += mPaddle.mDir * 300.0f * deltaTime;
        // Make sure paddle doesn't move off screen!
        if (mPaddle.my < (paddleH/2.0f + thickness))
        {
            mPaddle.my = paddleH/2.0f + thickness;
        }
        else if (mPaddle.my > (Global::GetWindowH() - paddleH/2.0f - thickness))
        {
            mPaddle.my = Global::GetWindowH() - paddleH/2.0f - thickness;
        }
    }

    // Update ball position based on ball velocity
    mBall.mx += mBall.mvx * deltaTime;
    mBall.my += mBall.mvy * deltaTime;

    // Bounce if needed
    // Did we intersect with the paddle?
    float diff = mPaddle.my - mBall.my;
    // Take absolute value of difference
    diff = (diff > 0.0f) ? diff : -diff;
    if (
            // Our y-difference is small enough
            diff <= paddleH / 2.0f &&
            // We are in the correct x-position
            mBall.mx <= 25.0f && mBall.mx >= 20.0f &&
            // The ball is moving to the left
            mBall.mvx < 0.0f)
    {
        mBall.mvx *= -1.0f;
    }
    // Did the ball go off the screen? (if so, end game)
    else if (mBall.mx <= 0.0f)
    {
        isRunning = false;
    }
    // Did the ball collide with the right wall?
    else if (mBall.mx >= (Global::GetWindowW() - thickness) && mBall.mvx > 0.0f)
    {
        mBall.mvx *= -1.0f;
    }

    // Did the ball collide with the top wall?
    if (mBall.my <= thickness && mBall.mvy < 0.0f)
    {
        mBall.mvy *= -1;
    }
    // Did the ball collide with the bottom wall?
    else if (mBall.my >= (Global::GetWindowH() - thickness) &&
             mBall.mvy > 0.0f)
    {
        mBall.mvy *= -1;
    }
}

void Pong::GenerateOutput()
{
    // Set draw color to blue
    SDL_SetRenderDrawColor(
                Global::renderer.get(),
                0,		// R
                0,		// G
                255,	// B
                255		// A
                );

    // Clear back buffer
    SDL_RenderClear(Global::renderer.get());

    // Draw walls
    SDL_SetRenderDrawColor(Global::renderer.get(), 255, 255, 255, 255);

    // Draw top wall
    SDL_Rect wall{
        0,			// Top left x
        0,			// Top left y
        Global::GetWindowW(),		// Width
        thickness	// Height
    };
    SDL_RenderFillRect(Global::renderer.get(), &wall);

    // Draw bottom wall
    wall.y = Global::GetWindowH() - thickness;
    SDL_RenderFillRect(Global::renderer.get(), &wall);

    // Draw right wall
    wall.x = Global::GetWindowW() - thickness;
    wall.y = 0;
    wall.w = thickness;
    wall.h = Global::GetWindowW();
    SDL_RenderFillRect(Global::renderer.get(), &wall);

    // Draw paddle
    SDL_Rect paddle{
        static_cast<int>(mPaddle.mx),
                static_cast<int>(mPaddle.my - paddleH/2),
                thickness,
                static_cast<int>(paddleH)
    };
    SDL_RenderFillRect(Global::renderer.get(), &paddle);

    // Draw ball
    SDL_Rect ball{
        static_cast<int>(mBall.mx - thickness/2),
                static_cast<int>(mBall.my - thickness/2),
                thickness,
                thickness
    };
    SDL_RenderFillRect(Global::renderer.get(), &ball);

    // Swap front buffer and back buffer
    SDL_RenderPresent(Global::renderer.get());
}
