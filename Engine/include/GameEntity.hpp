//GameEntity.hpp
#pragma once

#include <SDL2/SDL.h>
#include <memory>
#include <map>

#include "Component.hpp"
#include "ComponentType.hpp"
#include "TextureComponent.hpp"
#include "InputComponent.hpp"
#include "TransformComponent.hpp"
#include "Collision2DComponent.hpp"

struct GameEntity : public std::enable_shared_from_this<GameEntity> {
    GameEntity();

    virtual ~GameEntity();

    std::shared_ptr<GameEntity> GetThisPtr() {
        return shared_from_this();
    }

    virtual void Input(float deltaTime);

    virtual void Update(float deltaTime);

    virtual void Render(SDL_Renderer* renderer);

    // Checks whether two sprites interset (rockets).
    bool Intersects(std::shared_ptr<GameEntity> sceneObject);

    // NOTE: Could move this out of header eventually.
    template <typename T>
    void AddComponent(std::shared_ptr<T> c);

    template <typename T>
    std::shared_ptr<T> GetComponent(ComponentType type);

    void AddDefaultTransform();

    std::shared_ptr<TransformComponent> GetTransform();


    protected:
        // Assuming one component type per GameEntity.
        std::map<ComponentType, std::shared_ptr<Component>> mComponents;
};