// TextureComponent.hpp
#pragma once
#include <SDL2/SDL.h>
#include <memory>
#include <string>
#include "Component.hpp"

// A sprite is a texture that can move.
struct TextureComponent : public Component {
    TextureComponent();

    // Creates a sprite.
    void CreateTextureComponent(SDL_Renderer* renderer, std::string filePath);

    // Deconstructor.
    ~TextureComponent();

    ComponentType GetType() override;

    // Input
    void Input(float deltaTime) override;

    // Update
    void Update(float deltaTime) override;

    // Render
    void Render(SDL_Renderer* renderer) override;

    SDL_FRect GetRectangle() const;

    private:
        std::shared_ptr<SDL_Texture> mTexture;
};