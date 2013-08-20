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

namespace nafw
{
class Renderer;

/**
 *  Texture class
 */
class Texture
{
 public:
  // Constructor and Destructor
  Texture() : texture_(nullptr), width_(0), height_(0) {}
  ~Texture();

  // Mutators
  bool LoadFromFile(std::string path, Renderer* renderer);
  void SetColor(Uint8 r, Uint8 g, Uint8 b);
  void SetBlendMode(SDL_BlendMode blending);
  void SetAlpha(Uint8 alpha);
  void Free();

  // Accessors
  inline int GetWidth() const { return width_; }
  inline int GetHeight() const { return height_; }
  inline SDL_Texture *GetTexture() const { return texture_; }
 public:
  // Hardware texture
  SDL_Texture* texture_;

  // Image dimensions
  int width_, height_;
};

}

#endif//NAFW_TEXTURE_H_
