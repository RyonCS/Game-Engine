#include "TransformComponent.hpp"

// A sprite is a texture that can move.
TransformComponent::TransformComponent() {}

// Deconstructor.
TransformComponent::~TransformComponent() {}

// Input
void TransformComponent::Input(float deltaTime) {}

// Update
void TransformComponent::Update(float deltaTime) { }

// Render
void TransformComponent::Render(SDL_Renderer* renderer){}

ComponentType TransformComponent::GetType() {
    return ComponentType::TransformComponent;
}

// --- Getters and Setters ---
SDL_Rect TransformComponent::GetRectangle() const {
    return mRectangle;
}

void TransformComponent::SetW(float w) {
    mRectangle.w = w;
}

void TransformComponent::SetH(float h) {
    mRectangle.h = h;
}

void TransformComponent::SetWH(float w, float h) {
    mRectangle.w = w;
    mRectangle.h = h;
}

void TransformComponent::SetX(float x) {
    mRectangle.x = x;
}

void TransformComponent::SetY(float y) {
    mRectangle.y = y;
}

void TransformComponent::SetXY(float x, float y) {
    mRectangle.x = x;
    mRectangle.y = y;
}

float TransformComponent::GetW() const {
    return mRectangle.w;
}

float TransformComponent::GetH() const {
    return mRectangle.h;
}

float TransformComponent::GetX() const {
    return mRectangle.x;
}

float TransformComponent::GetY() const {
    return mRectangle.y;
}