//PlayerGameEntity.cpp
#include "PlayerGameEntity.hpp"


// Constructor 
PlayerGameEntity::PlayerGameEntity() {}

// Destructor.
PlayerGameEntity::~PlayerGameEntity() {}

/*!
 * Iterates through components assigned to PlayerGameEntity and calls Input on each of them.
 * 
 * @param - deltaTime. Time since last called.
 */
void PlayerGameEntity::Input(float deltaTime) {
    for(auto& [key, value] : mComponents) {
        mComponents[key]->Input(deltaTime);
    }
}

/*!
 * Iterates through components assigned to PlayerGameEntity and calls Update on each of them.
 * 
 * @param - deltaTime. Time since last called.
 */
void PlayerGameEntity::Update(float deltaTime) {
    for(auto& [key, value] : mComponents) {
        mComponents[key]->Update(deltaTime);
    }
}

/*!
 * Iterates through components assigned to PlayerGameEntity and calls Render on each of them.
 * 
 * @param - deltaTime. Time since last called.
 */
void PlayerGameEntity::Render(SDL_Renderer* renderer) {
    for (auto& [key, value] : mComponents) {
        mComponents[key]->Render(renderer);
    }
}