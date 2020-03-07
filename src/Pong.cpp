#include "Pong.h"

#include "Global_renderer.h"

Pong::Pong()
    : mTicksCount(0)
    , mPaddleDir(0)
{

}

bool Pong::Initialize()
{
    //
    mPaddlePos.x = 10.0f;
    mPaddlePos.y = 768.0f/2.0f;
    mBallPos.x = 1024.0f/2.0f;
    mBallPos.y = 768.0f/2.0f;
    mBallVel.x = -200.0f;
    mBallVel.y = 235.0f;

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
    mPaddleDir = 0;
    if (state[SDL_SCANCODE_W])
    {
        mPaddleDir -= 1;
    }
    if (state[SDL_SCANCODE_S])
    {
        mPaddleDir += 1;
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
    if (mPaddleDir != 0)
    {
        mPaddlePos.y += mPaddleDir * 300.0f * deltaTime;
        // Make sure paddle doesn't move off screen!
        if (mPaddlePos.y < (paddleH/2.0f + thickness))
        {
            mPaddlePos.y = paddleH/2.0f + thickness;
        }
        else if (mPaddlePos.y > (768.0f - paddleH/2.0f - thickness))
        {
            mPaddlePos.y = 768.0f - paddleH/2.0f - thickness;
        }
    }

    // Update ball position based on ball velocity
    mBallPos.x += mBallVel.x * deltaTime;
    mBallPos.y += mBallVel.y * deltaTime;

    // Bounce if needed
    // Did we intersect with the paddle?
    float diff = mPaddlePos.y - mBallPos.y;
    // Take absolute value of difference
    diff = (diff > 0.0f) ? diff : -diff;
    if (
            // Our y-difference is small enough
            diff <= paddleH / 2.0f &&
            // We are in the correct x-position
            mBallPos.x <= 25.0f && mBallPos.x >= 20.0f &&
            // The ball is moving to the left
            mBallVel.x < 0.0f)
    {
        mBallVel.x *= -1.0f;
    }
    // Did the ball go off the screen? (if so, end game)
    else if (mBallPos.x <= 0.0f)
    {
        isRunning = false;
    }
    // Did the ball collide with the right wall?
    else if (mBallPos.x >= (1024.0f - thickness) && mBallVel.x > 0.0f)
    {
        mBallVel.x *= -1.0f;
    }

    // Did the ball collide with the top wall?
    if (mBallPos.y <= thickness && mBallVel.y < 0.0f)
    {
        mBallVel.y *= -1;
    }
    // Did the ball collide with the bottom wall?
    else if (mBallPos.y >= (768 - thickness) &&
             mBallVel.y > 0.0f)
    {
        mBallVel.y *= -1;
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
        1024,		// Width
        thickness	// Height
    };
    SDL_RenderFillRect(Global::renderer.get(), &wall);

    // Draw bottom wall
    wall.y = 768 - thickness;
    SDL_RenderFillRect(Global::renderer.get(), &wall);

    // Draw right wall
    wall.x = 1024 - thickness;
    wall.y = 0;
    wall.w = thickness;
    wall.h = 1024;
    SDL_RenderFillRect(Global::renderer.get(), &wall);

    // Draw paddle
    SDL_Rect paddle{
        static_cast<int>(mPaddlePos.x),
                static_cast<int>(mPaddlePos.y - paddleH/2),
                thickness,
                static_cast<int>(paddleH)
    };
    SDL_RenderFillRect(Global::renderer.get(), &paddle);

    // Draw ball
    SDL_Rect ball{
        static_cast<int>(mBallPos.x - thickness/2),
                static_cast<int>(mBallPos.y - thickness/2),
                thickness,
                thickness
    };
    SDL_RenderFillRect(Global::renderer.get(), &ball);

    // Swap front buffer and back buffer
    SDL_RenderPresent(Global::renderer.get());
}
