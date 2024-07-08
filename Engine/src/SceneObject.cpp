//SceneObject.cpp
#include "SceneObject.hpp"


// Constructor -- creates a texture.
SceneObject::SceneObject() {}
SceneObject::SceneObject(SDL_Renderer* renderer) {}

// Destructor.
SceneObject::~SceneObject() {}

/*!
 * Iterates through all components assigned to a scene object and calls Input on them.
 * 
 * @param deltaTime - Time since last called.
 */
void SceneObject::Input(float deltaTime) {
    for(auto& [key, value] : mComponents) {
        mComponents[key]->Input(deltaTime);
    }
}

/*!
 * Iterates through all components assigned to a scene object and calls Update on them.
 * 
 * @param deltaTime - Time since last called.
 */
void SceneObject::Update(float deltaTime) {
    for(auto& [key, value] : mComponents) {
        mComponents[key]->Update(deltaTime);
    }
}

/*!
 * Iterates through all components assigned to a scene object and calls Render on them.
 * 
 * @param deltaTime - Time since last called.
 */
void SceneObject::Render(SDL_Renderer* renderer) {
    for (auto& [key, value] : mComponents) {
        mComponents[key]->Render(renderer);
    }
}