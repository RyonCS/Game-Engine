//Application.cpp
#include "Application.hpp"
#include "InputComponent.hpp"

// Constructor
Application::Application() {
    StartUp();
}

// Destructor
Application::~Application(){
    ShutDown();
}

/*!
 * Initializes SDL/Renderer. Loads in 3 scenes for program to load. Loads first scene.
 */
void Application::StartUp() {
    // Initialize SDL video and audio.
    if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO) != 0) {
        SDL_Log("Unable to initialize SDL: %s\n", SDL_GetError());
    }

    // Create Window.
    SDL_Window* mWindow = SDL_CreateWindow("An SDL2 Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_OPENGL);
    if (!mWindow) {
        SDL_Log("Error creating window: %s\n", SDL_GetError());
        return; // Exit if window creation fails.
    }
    m_window = mWindow;

    // Create Renderer.
    mRenderer = SDL_CreateRenderer(mWindow, 0, SDL_RENDERER_ACCELERATED);
    if(!mRenderer) {
        SDL_Log("Error creating renderer.");
    }

    // Load in our three sample scenes.
    std::vector<std::string>& scenes = mScene.getScenes();
    scenes.push_back("./../Scenes/level1.txt");
    scenes.push_back("./../Scenes/level2.txt");
    scenes.push_back("./../Scenes/level3.txt");

    int currentScene = mScene.getCurrentScene();

    // Load up our first scene.
    mScene.LoadSceneFromFile(scenes[currentScene], mRenderer);

    mScene.SetSceneStatus(true);
}

/*!
 * Destroys SDL window and quits program.
 */
void Application::ShutDown() {
    // Destroy window.
    SDL_DestroyWindow(mWindow);
    SDL_Quit();
}

/*!
 * Continuously checks if window-close button is pressed. If so, set the scene status to false (closing window);
 * 
 * @param deltaTime - Time passed since last call.
 */
void Application::Input(float deltaTime) {
    // Create an event struct to store an event popped off the queue.
    SDL_Event event;
    // Processing Input -- Only loops when there is an event.
    while(SDL_PollEvent(&event)) { // Pops off an event and puts it in 'event'.
        // If 'red x' is clicked, quit loop.
        if (event.type == SDL_QUIT) {
            SDL_Log("Program Quit: %u", event.quit.timestamp);
            mScene.SetSceneStatus(false);
        }
    }

    // Handle SDL_GetKeyBoardState after your SDL_Poll Event
    mScene.Input(deltaTime);
}

/*!
 * Updates by calling mScene.Update.
 * 
 * @param deltaTime - Time passed since last call.
 */
void Application::Update(float deltaTime) {
    mScene.Update(deltaTime);
}

/*!
 * Updates by calling mScene.Render()
 * 
 */
void Application::Render() {
    mScene.Render();
}

/*!
 * The main game loop. Limits FPS. Runs input, update, render.
 * 
 * @param targetFPS - The FPS for our program.
 */
void Application::Loop(float targetFPS) {
    // Our infinite game loop
    Uint64 lastTime, currentTime;
    lastTime = SDL_GetTicks();
    Uint64 framesElapsed=0;
    float deltaTime = 1.0f/targetFPS;

    while (mScene.GetSceneStatus()) {
        Uint64 startOfFrame = SDL_GetTicks();
        // We want IUR to take 16.666ms.
        Input(deltaTime);
        Update(deltaTime);
        Render();
        Uint64 elapsedTime = SDL_GetTicks() - startOfFrame;
        framesElapsed++;

        // Time keeping code - for frames elapsed.
        currentTime = SDL_GetTicks();
        // Insert a frame cap of 60 so it doesnt run too fast.
        if (elapsedTime < (1000/targetFPS)) {
            Uint64 delay = (1000/targetFPS) - elapsedTime;
            SDL_Delay(delay);
        }

        // If 1 second passes, report how many frames have been executed.
        if (currentTime > lastTime + 1000) {
            SDL_Log("1 Second Has Elapsed");
            SDL_Log("%llu", framesElapsed);
            deltaTime = 1.0f/framesElapsed;
            framesElapsed = 0;
            lastTime = SDL_GetTicks();
        }
    }
}

/*!
 * Returns the scene assigned to Application.
 * 
 * @return The scene assigned to Application.
 */
Scene Application::GetScene() {
    return mScene;
}

/*!
 * Handles keyboard events.
 * 
 * @return a vector of strings based on keyboard input.
 */
std::vector<std::string> Application::GetInput() {
    std::vector<std::string> keysPressed;

    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            mScene.SetSceneStatus(false);
            return keysPressed;
        }
    }

    // Handle keyboard inputs.
    const Uint8 *state = SDL_GetKeyboardState(NULL);
    if (state[SDL_SCANCODE_W]) {
        keysPressed.push_back("W");
        std::cout << "W pressed in C++" << std::endl;
    }
    if (state[SDL_SCANCODE_S]) {
        keysPressed.push_back("S");
    }
    if (state[SDL_SCANCODE_UP]) {
        keysPressed.push_back("UP");
    }
    if (state[SDL_SCANCODE_DOWN]) {
        keysPressed.push_back("DOWN");
    }
    if (state[SDL_SCANCODE_Q]) {
        keysPressed.push_back("Q");
    }
    if (state[SDL_SCANCODE_SPACE]) {
        keysPressed.push_back("SPACE");
    }

    return keysPressed;
}

/*!
 * Checks for quit event.
 * 
 */
void Application::Poll() {
    SDL_Event e;
    while(SDL_PollEvent(&e)) {
        if(e.type == SDL_QUIT) {
            mScene.SetSceneStatus(false);
            return; // Exit the loop if quit event is detected
        }
    }

    //Update screen of our specified window
    SDL_GL_SwapWindow(m_window);
}