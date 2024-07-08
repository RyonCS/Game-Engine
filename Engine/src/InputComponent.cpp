// InputComponent.hpp
#include "InputComponent.hpp"
#include "GameEntity.hpp"
#include "Scene.hpp"
#include <memory>

InputComponent::InputComponent() {}

// Deconstructor.
InputComponent::~InputComponent() {}


ComponentType InputComponent::GetType() {
    return ComponentType::InputComponent;
}

/*!
 * Handles keyboard input and some game logic to move player.
 * 
 * @param - deltaTime. Time since last called.
 */
void InputComponent::Input(float deltaTime) {
    const Uint8* state = SDL_GetKeyboardState(nullptr);
    auto ge = GetGameEntity();
    auto transform = ge->GetComponent<TransformComponent>(ComponentType::TransformComponent);
    if(state[SDL_SCANCODE_LEFT]){ // Move left.
        transform->SetX(transform->GetX() - mSpeed*deltaTime);
    } else if (state[SDL_SCANCODE_RIGHT]){ // Move right.
        transform->SetX(transform->GetX() + mSpeed*deltaTime);
    } else if (state[SDL_SCANCODE_UP]){ // Move up.
        transform->SetY(transform->GetY() - mSpeed*deltaTime);
    } else if (state[SDL_SCANCODE_DOWN]){ // Move down.
        transform->SetY(transform->GetY() + mSpeed*deltaTime);
    } 
}

// Update
void InputComponent::Update(float deltaTime) {}

// Render
void InputComponent::Render(SDL_Renderer* renderer) {}