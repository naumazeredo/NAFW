/**
 *  Not Available Framework
 *
 *  Texture Class
 *
 *  coded by Naum Azeredo <naumazeredo@gmail.com>
 *
 *  \brief Holds texture info, like width and height,
 *    Manages texture pointer, erasing pointer on destruction
 *
 */

#ifndef NAFW_TEXTURE_H_
#define NAFW_TEXTURE_H_

#include <string>
#include "../SDL2/SDL_stdinc.h"
#include "../SDL2/SDL_rect.h"
#include "../SDL2/SDL_render.h"

struct SDL_Texture;
struct SDL_Renderer;

namespace nafw
{

/**
 *  Texture class
 */
class Texture
{
 public:
  // Constructor and Destructor
  Texture() : texture_(nullptr), width_(0), height_(0), center_({0,0}), flip_(SDL_FLIP_NONE) {}
  ~Texture();

  // Mutators
  bool LoadFromFile(std::string path, SDL_Renderer* renderer);
  void SetColor(Uint8 r, Uint8 g, Uint8 b);
  void SetBlendMode(SDL_BlendMode blending);
  void SetAlpha(Uint8 alpha);
  void Free();

  inline void SetCenter(SDL_Point center) { center_ = center; }
  inline void SetFlip(SDL_RendererFlip flip) { flip_ = flip; }

  // Accessors
  inline int GetWidth() const { return width_; }
  inline int GetHeight() const { return height_; }
  inline SDL_Texture *GetTexture() const { return texture_; }
  inline SDL_Point GetCenter() const { return center_; }
  inline SDL_RendererFlip GetFlip() const { return flip_; }

  //
 public:
  // Hardware texture
  SDL_Texture* texture_;

  // Image dimensions
  int width_, height_;

  // Image center
  SDL_Point center_;

  // Flipping
  SDL_RendererFlip flip_;
};

}

#endif//NAFW_TEXTURE_H_
