//GameEntity.cpp
#include "GameEntity.hpp"

// Every gameEntity by default includes a transform.
GameEntity::GameEntity() {}

GameEntity::~GameEntity() {}

/*!
 * Iterates through components assigned to Game Entity and calls Input on each of them.
 * 
 * @param - deltaTime. Time since last called.
 */
void GameEntity::Input(float deltaTime) {
    for(auto& [key, value] : mComponents) {
        mComponents[key]->Input(deltaTime);
    }
}

/*!
 * Iterates through components assigned to Game Entity and calls Update on each of them.
 * 
 * @param - deltaTime. Time since last called.
 */
void GameEntity::Update(float deltaTime) {
    for(auto& [key, value] : mComponents) {
        mComponents[key]->Update(deltaTime);
    }
}

/*!
 * Iterates through components assigned to Game Entity and calls Render on each of them.
 * 
 * @param - deltaTime. Time since last called.
 */
void GameEntity::Render(SDL_Renderer* renderer) {
    for (auto& [key, value] : mComponents) {
        mComponents[key]->Render(renderer);
    }
}

/*!
 * Adds a component of any type to the Game Entity.
 * 
 * @param c - A component of any type.
 */
template <typename T>
void GameEntity::AddComponent(std::shared_ptr<T> c) {
    // Not: could use Template info to get exact component type.
    mComponents[c->GetType()] = c;
    c->SetGameEntity(GetThisPtr());
}

/*!
 * Returns the specifid component assigned to the game entity.
 * 
 * @param type - the type of component assigned to the game entity,
 * 
 * @return a pointer to the component requested.
 */
template <typename T>
std::shared_ptr<T> GameEntity::GetComponent(ComponentType type) {
    auto found = mComponents.find(type);
    if (found != mComponents.end()) {
        return dynamic_pointer_cast<T>(found->second);
    }
    // NOTE: better error messages -- don't show user this.
    SDL_Log("ERROR: The component you searched for is not found -- returning nullptr -- might segfault.");

    // Temporary way to handle component that doesn't exist.
    // Note: Maybe log as error?
    return nullptr;
}

/*!
 * Checks whether two game entities intersect.
 * 
 * @return true if intersect, else false.
 */
bool GameEntity::Intersects(std::shared_ptr<GameEntity> sceneObject) {
    auto source = sceneObject->GetComponent<Collision2DComponent>(ComponentType::Collision2DComponent)->GetRectangle();
    auto us     = GetComponent<Collision2DComponent>(ComponentType::Collision2DComponent)->GetRectangle();
    SDL_Rect result;
    bool intersects = SDL_IntersectRect(&source, &us, &result);
    
    return intersects;
}

/*!
 * Adds a transform component to the game entity.
 * 
 */
void GameEntity::AddDefaultTransform() {
    std::shared_ptr<TransformComponent> t = std::make_shared<TransformComponent>();
    AddComponent<TransformComponent>(t);
}

/*!
 * Returns the transform component.
 * 
 * @return the transform component.
 */
std::shared_ptr<TransformComponent> GameEntity::GetTransform() {
    return GetComponent<TransformComponent>(ComponentType::TransformComponent);
}


// Explicit Template Instantiation.
template void GameEntity::AddComponent<TextureComponent>(std::shared_ptr<TextureComponent> C);
// template void GameEntity::AddComponent<PositionComponent>(std::shared_ptr<PositionComponent> C);
template void GameEntity::AddComponent<TransformComponent>(std::shared_ptr<TransformComponent> C);
template void GameEntity::AddComponent<Collision2DComponent>(std::shared_ptr<Collision2DComponent> C);
template void GameEntity::AddComponent<InputComponent>(std::shared_ptr<InputComponent> C);

template std::shared_ptr<TextureComponent> GameEntity::GetComponent<TextureComponent>(ComponentType type);
// template std::shared_ptr<PositionComponent> GameEntity::GetComponent<PositionComponent>(ComponentType type);
template std::shared_ptr<TransformComponent> GameEntity::GetComponent<TransformComponent>(ComponentType type);
template std::shared_ptr<Collision2DComponent> GameEntity::GetComponent<Collision2DComponent>(ComponentType type);
template std::shared_ptr<InputComponent> GameEntity::GetComponent<InputComponent>(ComponentType type);