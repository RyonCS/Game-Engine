#pragma once
#include <SDL2/SDL.h>
#include <memory>

#include "ComponentType.hpp"

// Forward declaration of GameEntity which is included in our Component.
struct GameEntity;
struct PlayerGameEntity;

// Components must know about the gameEntity they are associated with.
// Components must have a type.
struct Component {
    Component(){}

    virtual ~Component(){}

    virtual void Input(float deltaTime) {}

    virtual void Update(float deltaTime) {}

    virtual void Render(SDL_Renderer* renderer) {}

    // Must be implemented.
    virtual ComponentType GetType()=0;

    void SetGameEntity(std::shared_ptr<GameEntity> g) {
        mGameEntity = g;
    }

    std::shared_ptr<GameEntity> GetGameEntity() {
        return mGameEntity;
    }

    public:
        std::shared_ptr<GameEntity> mGameEntity;
};