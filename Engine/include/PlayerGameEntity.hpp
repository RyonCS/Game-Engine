//PlayerGameEntity.hpp
#pragma once
#include "GameEntity.hpp"
#include "TextureComponent.hpp"

struct SDL_Renderer;

// Player Game Entity
struct PlayerGameEntity : public GameEntity {
    PlayerGameEntity();

    virtual ~PlayerGameEntity();

    // Input.
    virtual void Input(float deltaTime) override;

    // Update.
    virtual void Update(float deltaTime) override;

    // Render.
    void Render(SDL_Renderer* renderer) override;

    static std::shared_ptr<PlayerGameEntity> Create() {
        return std::make_shared<PlayerGameEntity>();
    }

    private:

};