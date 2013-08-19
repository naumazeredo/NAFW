#include <cmath>
#include "../SDL2/SDL_video.h"
#include "texture.h"
#include "renderer.h"

namespace nafw
{

Renderer::Renderer(SDL_Window* window, Uint32 flags)
{
  renderer_ = SDL_CreateRenderer(window, -1, flags);
  if (renderer_ == nullptr)
  {
    printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
    return;
  }

  SDL_SetRenderDrawColor(renderer_, 0xFF, 0xFF, 0xFF, 0xFF);

  // TODO initialize IMG
}

/*
bool Renderer::Init(SDL_Window* window, Uint32 flags)
{
  renderer_ = SDL_CreateRenderer(window, -1, flags);
  if (renderer_ == nullptr)
  {
    printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
    return false;
  }

  SDL_SetRenderDrawColor(renderer_, 0xFF, 0xFF, 0xFF, 0xFF);

  // TODO initialize IMG

  return true;
}
*/

Renderer::~Renderer()
{
  if (renderer_ != nullptr)
    SDL_DestroyRenderer(renderer_);
}

void Renderer::DrawTexture(Texture* texture, const SDL_Rect* clip, const double scale, const double angle)
{
  SDL_Rect scalerect;
  scalerect.x = clip->x * scale;
  scalerect.y = clip->y * scale;
  scalerect.w = clip->w * scale;
  scalerect.h = clip->h * scale;
  SDL_Point center = texture->GetCenter();
  SDL_RenderCopyEx(renderer_, texture->GetTexture(), clip, &scalerect, angle, &center, texture->GetFlip());
}

void Renderer::DrawLine(SDL_Point start, SDL_Point end, SDL_Color color)
{
  Uint8 r, g, b, a;
  SDL_GetRenderDrawColor(renderer_, &r, &g, &b, &a);
  SDL_SetRenderDrawColor(renderer_, color.r, color.g, color.b, color.a);
  SDL_RenderDrawLine(renderer_, start.x, start.y, end.x, end.y);
  SDL_SetRenderDrawColor(renderer_, r, g, b, a);
}

void Renderer::DrawRect(SDL_Rect rect, SDL_Color color)
{
  Uint8 r, g, b, a;
  SDL_GetRenderDrawColor(renderer_, &r, &g, &b, &a);
  SDL_SetRenderDrawColor(renderer_, color.r, color.g, color.b, color.a);
  SDL_RenderDrawRect(renderer_, &rect);
  SDL_SetRenderDrawColor(renderer_, r, g, b, a);
}

void Renderer::DrawFillRect(SDL_Rect rect, SDL_Color color)
{
  Uint8 r, g, b, a;
  SDL_GetRenderDrawColor(renderer_, &r, &g, &b, &a);
  SDL_SetRenderDrawColor(renderer_, color.r, color.g, color.b, color.a);
  SDL_RenderFillRect(renderer_, &rect);
  SDL_SetRenderDrawColor(renderer_, r, g, b, a);
}

void Renderer::DrawCircle(SDL_Point center, float radius, SDL_Color color, float arc_delta)
{
  Uint8 r, g, b, a;
  SDL_GetRenderDrawColor(renderer_, &r, &g, &b, &a);
  SDL_SetRenderDrawColor(renderer_, color.r, color.g, color.b, color.a);

  float angle = 0.0f;

  float rad_arc = arc_delta * M_PI / 180.0f;
  for (; angle <= 2 * M_PI - rad_arc; angle += rad_arc)
  {
    SDL_RenderDrawLine(
      renderer_,
      center.x + radius * sin(angle),
      center.y + radius * cos(angle),
      center.x + radius * sin(angle + rad_arc),
      center.y + radius * cos(angle + rad_arc)
    );
  }

  if (angle < M_PI)
  {
    SDL_RenderDrawLine(
      renderer_,
      center.x + radius * sin(angle),
      center.y + radius * cos(angle),
      center.x + radius * sin(2 * M_PI),
      center.y + radius * cos(2 * M_PI)
    );
  }

  SDL_SetRenderDrawColor(renderer_, r, g, b, a);
}

void Renderer::ClearScreen()
{
  SDL_RenderClear(renderer_);
}

void Renderer::RenderScreen()
{
  SDL_RenderPresent(renderer_);
}

}
