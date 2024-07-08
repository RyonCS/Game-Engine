//Scene.hpp
#pragma once

#include <SDL2/SDL.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <memory>

#include "GameEntity.hpp"
#include "PlayerGameEntity.hpp"
#include "ComponentType.hpp"
#include "Component.hpp"
#include "SceneObject.hpp"


struct Scene {
    // Constructor
    Scene();
    ~Scene();

    // START UP + SHUTDOWN
    void CreateNewGameEntity(std::string type, int x_position, int y_position);
    void ShutDown();

    void LoadSceneFromFile(std::string fileName, SDL_Renderer* renderer);

    // Input, update, render.
    void Input(float deltaTime);
    void Update(float deltaTime);
    void Render();

    void SetSceneStatus(bool status);

    bool GetSceneStatus() const;

    std::shared_ptr<PlayerGameEntity> GetMainCharacter();

    std::vector<std::string>& getScenes();

    int getCurrentScene() {
        return m_currentScene;
    }

    private:
        // Main character.
        std::shared_ptr<PlayerGameEntity> m_mainCharacter;

        std::vector<std::shared_ptr<SceneObject>> m_sceneObjects;

        std::shared_ptr<SceneObject> m_winner;

        std::vector<std::string> m_Scenes;

        SDL_Renderer* mRenderer;

        bool mSceneIsActive{false};

        bool sceneComplete{false};

        int m_currentScene = 0;
};