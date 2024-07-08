// ResourceManager.cpp
#include "ResourceManager.hpp"

/*!
 * Makes a shared texture from the pixels of a .bmp file loaded in.
 * 
 * @param renderer - Our renderer.
 * @param pixels - the data from a loaded in .bmp file.
 * 
 * @return a shared pointer to an SDL_Texture.
 */
std::shared_ptr<SDL_Texture> make_shared_texture(SDL_Renderer* renderer, SDL_Surface* pixels) {
        SDL_Texture* pTexture = SDL_CreateTextureFromSurface(renderer, pixels);

        if (nullptr == pTexture) {
                SDL_Log("Could not load texture from surface.");
        }
        return std::shared_ptr<SDL_Texture>(pTexture, TextureFunctorDeleter());
    }