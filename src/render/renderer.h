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

#include <map>
#include <string>
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

// TODO Gather all drawing to do one
class Renderer
{
 public:
  // Constructor and Destructor
  Renderer() {}
  Renderer(SDL_Window* window, Uint32 flags);
  ~Renderer();

  // Return Renderer
  inline SDL_Renderer* GetRenderer() const { return renderer_; }

  // Texture draw
  //void DrawTexture(Texture* texture, SDL_Point position, const SDL_Rect* clip = nullptr, const double scale = 1.0, const double angle = 0.0);
  void DrawTexture(Texture* texture, SDL_Point position, bool flip = false);   // Basic texture drawing
  void DrawTexture(Texture* texture, SDL_Point position, const SDL_Rect* clip, bool flip = false);   // Clipped drawing
  void DrawTexture(Texture* texture, SDL_Point position, const SDL_Rect* clip, const float scale, bool flip = false);    // Scaled, clipped drawing
  void DrawTexture(Texture* texture, SDL_Point position, const SDL_Rect* clip, const float scale, const SDL_Point* center, const double angle, bool flip = false); // Rotated, scaled, clipped drawing

  // Basic draw
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
