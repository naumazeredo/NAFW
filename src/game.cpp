#include <cstdio>
#include "SDL2/SDL.h"
#include "game.h"
#include "timer.h"

namespace nafw
{

Game::Game()
{
  window_ = nullptr;
  timer_ = new Timer();
}

Game::~Game()
{
  if (window_ != nullptr)
    SDL_DestroyWindow(window_);
  if (timer_ != nullptr)
    delete timer_;
}

bool Game::Start(const char* title, int argc, char** argv)
{
  // Init SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0)
  {
    printf("Could not init SDL: %s\n", SDL_GetError());
    return false;
  }

  // Create window
  window_ = SDL_CreateWindow(
    title,
    SDL_WINDOWPOS_CENTERED,
    SDL_WINDOWPOS_CENTERED,
    WINDOW_WIDTH,
    WINDOW_HEIGHT,
    SDL_WINDOW_SHOWN
  );
  if (window_ == NULL)
  {
    printf("Could not create window: %s\n", SDL_GetError());
    return false;
  }

  return true;
}

bool Game::HandleInputs()
{
  // Basic Inputs
  SDL_Event event;
  while (SDL_PollEvent(&event))
  {
    if (event.type == SDL_QUIT )
      return true;

    if (event.type == SDL_KEYDOWN)
    {
      if (event.key.keysym.sym == SDLK_F4 && (event.key.keysym.mod & KMOD_LALT))
        return true;
    }
  }

  return false;
}

bool Game::Run()
{
  physics_dt = 10;
  int physics_accum = 0;

  // FIXME network_dt must be in the network environment
  int network_dt = 30;
  int network_accum = 0;

  //int current_time = SDL_GetTicks();

  timer_->Init();

  bool quit = false;
  while (!quit)
  {
    // Update timer
    //int old_time = current_time;
    //current_time = SDL_GetTicks();
    timer_->NextFrame();

    physics_accum += timer_->GetDelta();//current_time - old_time;
    network_accum += timer_->GetDelta();//current_time - old_time;
    while (physics_accum >= physics_dt || network_accum >= network_dt)
    {
      // Networking
      // Server->Client
      // TODO Verify if received a socket

      // Client->Server
      if (network_accum >= network_dt)
      {
        // Handle User Inputs
        if (HandleInputs())
        {
          quit = true;

          /* TODO Send disconnect to server */
          break;
        }

        /* TODO Send file */

        // Update accumulator
        network_accum -= network_dt;
      }

      /* TODO Send update to server */

      // Physics
      if (physics_accum >= physics_dt)
      {
        /* TODO Step physics */

        // Update accumulator
        physics_accum -= physics_dt;
      }
    }

    /* TODO Integrate the exceding time in physics */

    /* TODO Render */
  }

  // Finish game
  return false;
}

}
