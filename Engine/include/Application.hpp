//Application.hpp
#pragma once

#include <SDL2/SDL.h>
#include <iostream>
#include <vector>
#include <memory>

#include "GameEntity.hpp"
#include "PlayerGameEntity.hpp"
#include "ComponentType.hpp"
#include "Component.hpp"
#include "Scene.hpp"

struct Application {
    // Constructor
    Application();
    ~Application();

    /*!
    * Testing Doxygen comment for Application::Startup in .hpp
    */
    void StartUp();

    
    void ShutDown();

    // Input, update, render.
    void Input(float deltaTime);
    void Update(float deltaTime);
    void Render();

    // Main game loop.
    void Loop(float targetFPS);

    Scene GetScene();

    std::vector<std::string> GetInput();

    void Poll();

    private:
        // Note: Let's just have one scene.
        // Consider if this should be a pointer.
        // Consider if thi should be a vector or a linked list.
        Scene mScene;
        SDL_Window* m_window;

        bool            mRun{true};
        SDL_Window*     mWindow;
        SDL_Renderer*   mRenderer;
};