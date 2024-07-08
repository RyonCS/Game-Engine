//PlayerGameEntity.hpp
#pragma once
#include "GameEntity.hpp"
#include "TextureComponent.hpp"


// Object
struct SceneObject : public GameEntity {
    SceneObject();
    SceneObject(SDL_Renderer* renderer);

    virtual ~SceneObject();

    // Input.
    virtual void Input(float deltaTime);

    // Update.
    virtual void Update(float deltaTime);

    // Render.
    void Render(SDL_Renderer* renderer);

    private:
        
};