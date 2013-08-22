#include <cstdio>
#include "../SDL2/SDL.h"
#include "../SDL2/SDL_image.h"
#include "renderer.h"
#include "texture.h"

namespace nafw
{

Texture::~Texture()
{
  Free();
}

bool Texture::Load(std::string path)
{
  SDL_assert(renderer_!=nullptr);

  // Deallocate texture
  Free();

  // Load image
  SDL_Surface* surface = IMG_Load(path.c_str());
  if (surface == nullptr)
  {
    printf("Could not load image: %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
  }
  else
  {
    // Color key image
    //SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, 0xFF, 0, 0xFF));

    // Create texture from surface pixels
    texture_ = SDL_CreateTextureFromSurface(renderer_->GetRenderer(), surface);
    if (texture_ == nullptr)
    {
      printf("Could not create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
    }
    else
    {
      // Get dimensions
      width_ = surface->w;
      height_ = surface->h;
    }

    // Free old surface
    SDL_FreeSurface(surface);
  }

  path_ = path;
  loaded_ = true;

  // Return success
  return texture_ != nullptr;
}

void Texture::SetColor(Uint8 r, Uint8 g, Uint8 b)
{
  SDL_assert(!loaded_);
  // Modulate texture rgb
  SDL_SetTextureColorMod(texture_, r, g, b);
}

void Texture::SetBlendMode(SDL_BlendMode blending)
{
  SDL_assert(!loaded_);
  // Set blending function
  SDL_SetTextureBlendMode(texture_, blending);
}

void Texture::SetAlpha(Uint8 alpha)
{
  SDL_assert(!loaded_);
  // Modulate texture alpha
  SDL_SetTextureAlphaMod(texture_, alpha);
}

SDL_Texture* Texture::GetTexture()
{
  SDL_assert(!loaded_);
  return texture_;
}

void Texture::Free()
{
  if (loaded_ && texture_ != nullptr)
  {
    SDL_DestroyTexture(texture_);
    width_ = 0;
    height_ = 0;
    loaded_ = false;
    path_.erase();
  }
}

}

