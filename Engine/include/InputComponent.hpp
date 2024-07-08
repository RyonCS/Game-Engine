// InputComponent.hpp
#pragma once
#include <SDL2/SDL.h>
#include <memory>
#include <string>
#include "Component.hpp"
#include <vector>
#include <string>

// A Input is a texture that can move.
struct InputComponent : public Component {
    InputComponent();

    // Deconstructor.
    ~InputComponent();

    ComponentType GetType() override;

    // Input
    void Input(float deltaTime) override;

    // Update
    void Update(float deltaTime) override;

    // Render
    void Render(SDL_Renderer* renderer) override;

    private:
        float mSpeed{100};
};