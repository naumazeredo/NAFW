#include <cstdio>
#include <cmath>
#include "../SDL2/SDL_video.h"
#include "../SDL2/SDL_image.h"
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
  if (!IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)
  {
    printf("SDL_image could not be initialized! SDL image error: %s\n", IMG_GetError());
    return;
  }
}

Renderer::~Renderer()
{
  if (renderer_ != nullptr)
    SDL_DestroyRenderer(renderer_);
}

void Renderer::DrawTexture(Texture* texture, SDL_Point position, bool flip)
{
  DrawTexture(texture, position, NULL, 1.0f, NULL, 0.0, flip);
}

void Renderer::DrawTexture(Texture* texture, SDL_Point position, const SDL_Rect* clip, bool flip)
{
  DrawTexture(texture, position, clip, 1.0f, NULL, 0.0, flip);
}

void Renderer::DrawTexture(Texture* texture, SDL_Point position, const SDL_Rect* clip, const float scale, bool flip)
{
  DrawTexture(texture, position, clip, scale, NULL, 0.0, flip);
}

void Renderer::DrawTexture(Texture* texture, SDL_Point position, const SDL_Rect* clip, const float scale, const SDL_Point* center, const double angle, bool flip)
{
  SDL_Rect scalerect;
  scalerect = {
    position.x,
    position.y,
    (clip != nullptr ? static_cast<int>(clip->w * scale) : static_cast<int>(texture->GetWidth() * scale)),
    (clip != nullptr ? static_cast<int>(clip->h * scale) : static_cast<int>(texture->GetHeight() * scale))
  };
  SDL_RenderCopyEx(renderer_, texture->GetTexture(), clip, &scalerect, angle, center, (flip ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE));
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
