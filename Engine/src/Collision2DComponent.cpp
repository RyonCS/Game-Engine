#include "Collision2DComponent.hpp"
#include "GameEntity.hpp"

Collision2DComponent::Collision2DComponent() {}

Collision2DComponent::~Collision2DComponent() {}

void Collision2DComponent::Input(float deltaTime) {}

/*!
 * Updates Collision Component based on Game Entity's transform x, y, w, h.
 * 
 */
void Collision2DComponent::Update(float deltaTime) {
    // NOTE:: Default behavior will be to update collison component with the object's transform.
    // Later we may want to have more control.
    auto transform = GetGameEntity()->GetTransform();
    SetWH(transform->GetW(), transform->GetH());
    SetXY(transform->GetX(), transform->GetY());
}

/*!
 * Draws a rectangle around the game entity.
 * 
 * @param renderer - Our Renderer.
 */
void Collision2DComponent::Render(SDL_Renderer* renderer){
    // Useful for debugging purposes.
    SDL_RenderDrawRect(renderer, &mRectangle);
}

/*!
 * Returns the component type.
 * 
 * @return the component type.
 */
ComponentType Collision2DComponent::GetType() {
    return ComponentType::Collision2DComponent;
}

// --- Getters and Setters ---
SDL_Rect Collision2DComponent::GetRectangle() const {
    return mRectangle;
}

void Collision2DComponent::SetW(float w) {
    mRectangle.w = w;
}

void Collision2DComponent::SetH(float h) {
    mRectangle.h = h;
}

void Collision2DComponent::SetWH(float w, float h) {
    mRectangle.w = w;
    mRectangle.h = h;
}

void Collision2DComponent::SetX(float x) {
    mRectangle.x = x;
}

void Collision2DComponent::SetY(float y) {
    mRectangle.y = y;
}

void Collision2DComponent::SetXY(float x, float y) {
    mRectangle.x = x;
    mRectangle.y = y;
}

float Collision2DComponent::GetW() const {
    return mRectangle.w;
}

float Collision2DComponent::GetH() const {
    return mRectangle.h;
}

float Collision2DComponent::GetX() const {
    return mRectangle.x;
}

float Collision2DComponent::GetY() const {
    return mRectangle.y;
}