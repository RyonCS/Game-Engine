// ResourceManager.hpp
#pragma once
#include "SDL2/SDL.h"
#include <SDL2/SDL_surface.h>
#include <unordered_map>
#include <string>
#include <iostream>


// Custom Deleter
struct TextureFunctorDeleter {
    void operator()(SDL_Texture* texture) const {
        SDL_DestroyTexture(texture);
    }
};

// Make a shared pointer out of our texture.
std::shared_ptr<SDL_Texture> make_shared_texture(SDL_Renderer* renderer, SDL_Surface* pixels);

struct ResourceManager {
    // Creates a singleton resource.
    static ResourceManager& Instance() {
        if (nullptr == mInstance) {
            mInstance = new ResourceManager();
        }
        return *mInstance;
    }

    // Load a texture from disk into a map.
    std::shared_ptr<SDL_Texture>  LoadTexture(SDL_Renderer* renderer, std::string filePath) {
        if (!renderer) {
            SDL_Log("Error with Renderer in LoadTexture: %s\n", SDL_GetError());
        }
        std::cout << "File Path" << filePath << std::endl;
        auto iterator = mTextureResources.find(filePath);
        if (iterator == mTextureResources.end()) {

            // Load an asset.
            SDL_Surface* pixels = SDL_LoadBMP(filePath.c_str());
            if (!pixels) {
                SDL_Log("Error loading BMP: %s\n", SDL_GetError());
            }
            SDL_SetColorKey(pixels, SDL_TRUE, SDL_MapRGB(pixels->format, 0xFF, 0, 0xFF));

            std::shared_ptr<SDL_Texture> pTexture = make_shared_texture(renderer, pixels);
            
            // Add to map.
            mTextureResources.insert({filePath, pTexture});

            // Destory Pixels.
            //SDL_DestroySurface(pixels); 
            SDL_Log("Created new resource %s", filePath.c_str());
        } else {
            SDL_Log("Created new resource %s", filePath.c_str());
        }
        return mTextureResources[filePath];  
    }

    private:
        ResourceManager(){}
        inline static ResourceManager* mInstance = nullptr;
        std::unordered_map<std::string, std::shared_ptr<SDL_Texture>> mTextureResources;
        // mTextureResources[filePath] = texture;
};