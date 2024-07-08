// TransformComponent.hpp
#pragma once
#include <SDL2/SDL.h>
#include <memory>
#include <string>
#include <iostream>
#include "Component.hpp"

// A sprite is a texture that can move.
struct TransformComponent : public Component {
    TransformComponent();

    // Deconstructor.
    ~TransformComponent();

    ComponentType GetType() override;

    void Input(float deltaTime) override;

    void Update(float deltaTime) override;

    void Render(SDL_Renderer* renderer) override;

    void SetW(float w);
    void SetH(float h);
    void SetWH(float w, float h);
    void SetX(float x);
    void SetY(float y);
    void SetXY(float x, float y);

    float GetH() const;
    float GetW() const;
    float GetX() const;
    float GetY() const;

    SDL_Rect GetRectangle() const;

    private:
        SDL_Rect mRectangle{20, 20, 20, 20};
        std::shared_ptr<SDL_Texture> mTexture;
};