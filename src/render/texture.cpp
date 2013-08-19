#include <cstdio>
#include "../SDL2/SDL.h"
#include "../SDL2/SDL_image.h"
#include "texture.h"

namespace nafw
{

Texture::~Texture()
{
  Free();
}

bool Texture::LoadFromFile(std::string path, SDL_Renderer* renderer)
{
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
    texture_ = SDL_CreateTextureFromSurface(renderer, surface);
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

  // Return success
  return texture_ != nullptr;
}

void Texture::SetColor(Uint8 r, Uint8 g, Uint8 b)
{
  // Modulate texture rgb
  SDL_SetTextureColorMod(texture_, r, g, b);
}

void Texture::SetBlendMode(SDL_BlendMode blending)
{
  // Set blending function
  SDL_SetTextureBlendMode(texture_, blending);
}

void Texture::SetAlpha(Uint8 alpha)
{
  // Modulate texture alpha
  SDL_SetTextureAlphaMod(texture_, alpha);
}

void Texture::Free()
{
  if (texture_ != nullptr)
  {
    SDL_DestroyTexture(texture_);
    texture_ = nullptr;
    width_ = 0;
    height_ = 0;
  }
}

}

