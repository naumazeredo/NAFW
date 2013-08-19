/**
 *  Not Available Framework
 *
 *  Renderer Class
 *
 *  coded by Naum Azeredo <naumazeredo@gmail.com>
 *
 *  \brief Holds, manages and draws game textures
 *
 */

#ifndef NAFW_RENDERER_H_
#define NAFW_RENDERER_H_

#include "../SDL2/SDL_stdinc.h"
#include "../SDL2/SDL_rect.h"
#include "../SDL2/SDL_render.h"
#include "constants.h"

struct SDL_Window;
struct SDL_Renderer;

namespace nafw
{

//extern SDL_Color white;

class Texture;

class Renderer
{
 public:
  // Constructor and Destructor
  Renderer() {}
  Renderer(SDL_Window* window, Uint32 flags);
  ~Renderer();

  // Init renderer
  //bool Init(SDL_Window* window, Uint32 flags = SDL_RENDERER_ACCELERATED);

  //
  void DrawTexture(Texture* texture, const SDL_Rect* clip, const double scale = 1.0, const double angle = 0.0);
  void DrawLine(SDL_Point start, SDL_Point end, SDL_Color color = Color::black);
  void DrawRect(SDL_Rect rect, SDL_Color color = Color::black);
  void DrawFillRect(SDL_Rect rect, SDL_Color color = Color::black);
  void DrawCircle(SDL_Point center, float radius, SDL_Color color = Color::black, float arc_delta=5.0f);

  void ClearScreen();
  void RenderScreen();

 private:
  // SDL Renderer
  SDL_Renderer* renderer_ = nullptr;
};

}

#endif//NAFW_RENDERER_H_
