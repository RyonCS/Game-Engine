//Scene.cpp
#include "Scene.hpp"
#include "InputComponent.hpp"

// Constructor
Scene::Scene() {
}

// Destructor
Scene::~Scene(){
    ShutDown();
}

/*!
 * Creates a new game entity. Player, grass, rock, or winner based on parameter.
 * 
 * @param type - The type of game entity.
 * @param x_position - The entity's x-coordinate.
 * @param y_position - The entity's y-coordinate.
 */
void Scene::CreateNewGameEntity(std::string type, int x_position, int y_position) {
    // Create a player Game Entity.
    if (type == "player") {
        // Create and add transform component.
        m_mainCharacter = std::make_shared<PlayerGameEntity>();
        m_mainCharacter->AddDefaultTransform();
        m_mainCharacter->GetTransform()->SetXY(x_position, y_position);
    
        // Load and add texture.
        std::shared_ptr<TextureComponent> characterTexture = std::make_shared<TextureComponent>();
        characterTexture->CreateTextureComponent(mRenderer, "./../Assets/Slime.bmp");
        m_mainCharacter->AddComponent(characterTexture);

        // Add input controller.        
        std::shared_ptr<InputComponent> inputController = std::make_shared<InputComponent>();
        inputController->SetGameEntity(m_mainCharacter);
        m_mainCharacter->AddComponent(inputController);

        // Add and set collision component.
        std::shared_ptr<Collision2DComponent> collision = std::make_shared<Collision2DComponent>();
        collision->SetXY(x_position, y_position);
        m_mainCharacter->AddComponent(collision);
    }
    // Create a sceneObject Game Entity of type grass.
    if (type == "grass") {
        // Create object and add transform component.
        std::shared_ptr<SceneObject> sceneObject = std::make_shared<SceneObject>();
        sceneObject->AddDefaultTransform();
        sceneObject->GetTransform()->SetXY(x_position, y_position);

        // Create and add texture.
        std::shared_ptr<TextureComponent> texture = std::make_shared<TextureComponent>();
        texture->CreateTextureComponent(mRenderer, "./../Assets/Grass.bmp");
        sceneObject->AddComponent(texture);

        // Create, position, and add collision component.
        std::shared_ptr<Collision2DComponent> collision = std::make_shared<Collision2DComponent>();
        collision->SetXY(x_position, y_position);
        sceneObject->AddComponent(collision);
        
        // Add to list of scene objects.
        m_sceneObjects.push_back(sceneObject);
    }
    // Create a sceneObject Game Entity of type rock.
    if (type == "rock") {
        // Create object and add transform component.
        std::shared_ptr<SceneObject> sceneObject = std::make_shared<SceneObject>();
        sceneObject->AddDefaultTransform();
        sceneObject->GetTransform()->SetXY(x_position, y_position);

        // Load and add texture.
        std::shared_ptr<TextureComponent> texture = std::make_shared<TextureComponent>();
        texture->CreateTextureComponent(mRenderer, "./../Assets/Rock.bmp");
        sceneObject->AddComponent(texture);

        // Add collision component.
        std::shared_ptr<Collision2DComponent> collision = std::make_shared<Collision2DComponent>();
        collision->SetXY(x_position, y_position);
        sceneObject->AddComponent(collision);

        // Add component to list of scene objects.
        m_sceneObjects.push_back(sceneObject);
    }
    // Create a sceneObject Game Entity of type winner.
    if(type == "winner") {
        // Create object and add transform component.
        std::shared_ptr<SceneObject> sceneObject = std::make_shared<SceneObject>();
        sceneObject->AddDefaultTransform();
        sceneObject->GetTransform()->SetXY(x_position, y_position);

        // Load and add texture.
        std::shared_ptr<TextureComponent> texture = std::make_shared<TextureComponent>();
        texture->CreateTextureComponent(mRenderer, "./../Assets/winner.bmp");
        sceneObject->AddComponent(texture);

        // Load and add collision component.
        std::shared_ptr<Collision2DComponent> collision = std::make_shared<Collision2DComponent>();
        sceneObject->AddComponent(collision);

        // Assign component as winner object.
        m_winner = sceneObject;
    }
}

/*!
 * Reads a .txt file of a scene and loads in Game Entities.
 * 
 * @param fileName - The name of a scene/level file.
 * @param renderer - Our renderer.
 */
void Scene::LoadSceneFromFile(std::string fileName, SDL_Renderer* renderer) {
    mRenderer = renderer;

    std::ifstream file(fileName);
    std::string line;

    if (!file.is_open()) {
        std::cout << "Error loading file." << std::endl;
        exit(1);
    }

    // Read enemies locations from a text file.
    while(std::getline(file, line)) {
        std::istringstream iss(line);
        // Get Entity type and position.
        std::string type;
        int x_position;
        int y_position;
        
        iss >> type;
        iss >> x_position;
        iss >> y_position;

        // Create new entity from type and position.
        CreateNewGameEntity(type, x_position, y_position);
    }
}

void Scene::ShutDown() {}

/*!
 * The bulk of the program which handles input. Checks for collision from player and scene objects and checks if player won by reaching the star.
 * 
 * @param deltaTime - The time since last call.
 */
void Scene::Input(float deltaTime) {

    // Get the main character and objects previous positions before collision.
    float character_prevX = m_mainCharacter->GetTransform()->GetX();
    float character_prevY = m_mainCharacter->GetTransform()->GetY();
    float sceneObject_x;
    float sceneObject_y;

    // Get main character's input.
    m_mainCharacter->Input(deltaTime);

    // If there's an intersection between the player and an object, set bool to true.
    bool intersects;
    for(int i = 0; i < m_sceneObjects.size(); i++) {
        if (m_mainCharacter->Intersects(m_sceneObjects[i])) {
            sceneObject_x = m_sceneObjects[i]->GetTransform()->GetX();
            sceneObject_y = m_sceneObjects[i]->GetTransform()->GetY();
            intersects = true;
            break;
        }
    }
    // If there was an intersection, find out which side it occured on and move the player away from that side.
    // This helps prevent sticking to a game object in a permanent intersection.
    if (intersects) {
        // Calculate the distance between the main character and the scene object.
        float deltaX = character_prevX - sceneObject_x;
        float deltaY = character_prevY - sceneObject_y;

        // Check which side the intersection occurred on.
        if (std::abs(deltaX) > std::abs(deltaY)) {
            // Intersection occurred on the left or right side.
            if (deltaX > 0) {
                // Intersection occurred on the left side.
                m_mainCharacter->GetTransform()->SetX(sceneObject_x + 20);
            } else {
                // Intersection occurred on the right side.
                m_mainCharacter->GetTransform()->SetX(sceneObject_x - 20);
            }
        } else {
            // Intersection occurred on the top or bottom side.
            if (deltaY > 0) {
                // Intersection occurred on the top side.
                m_mainCharacter->GetTransform()->SetY(sceneObject_y + 20);
            } else {
                // Intersection occurred on the bottom side.
                m_mainCharacter->GetTransform()->SetY(sceneObject_y - 20);
            }
        }
    }

    // If the player intersects with the winner object. Load the next scene.
    if (m_mainCharacter->Intersects(m_winner)) {
        m_currentScene += 1;
        // Delay - so intersection from previous scene doesn't ruin next scene.
        SDL_Delay(100);
        // If there are more scenes to load, load the next one.
        if (m_currentScene < m_Scenes.size()) {
            // Clear all of our game entities.
            m_mainCharacter.reset();
            m_sceneObjects.clear();
            m_winner.reset();
            // Load in new scene.
            LoadSceneFromFile(m_Scenes[m_currentScene], mRenderer);
        } else {
            // If there are no more scenes to load, close program.
            mSceneIsActive = false;
        }
    }
}

/*!
 * Updates game entities.
 * 
 * @param deltaTime - Time since last called.
 */
void Scene::Update(float deltaTime) {
    for(int i = 0; i < m_sceneObjects.size(); i++) {
        m_sceneObjects[i]->Update(deltaTime);
    }
    m_mainCharacter->Update(deltaTime);
    m_winner->Update(deltaTime);
}

/*!
 * Renders game entities.
 * 
 */
void Scene::Render() {
    SDL_SetRenderDrawColor(mRenderer, 32, 32, 64, SDL_ALPHA_OPAQUE);
    if (!mRenderer) {
            SDL_Log("Error with Renderer in Scene::Render: %s\n", SDL_GetError());
        }
    SDL_RenderClear(mRenderer);

    // Update enemies.
    SDL_SetRenderDrawColor(mRenderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
    for(int i = 0; i < m_sceneObjects.size(); i++) {
        m_sceneObjects[i]->Render(mRenderer);
    }

    // Render main character.
    m_mainCharacter->Render(mRenderer);
    m_winner->Render(mRenderer);
    
    SDL_RenderPresent(mRenderer);   
}

/*!
 * Set the scene status.
 * 
 * @param status - Bool.
 */
void Scene::SetSceneStatus(bool status){
    mSceneIsActive = status;
}

/*!
 * Returns the scene status.
 * 
 * @return the current scene status.
 */
bool Scene::GetSceneStatus() const {
    return mSceneIsActive;
}

/*!
 * Returns a pointer to the main character game entity.
 * 
 * @return a pointer to the main character game entity.
 */
std::shared_ptr<PlayerGameEntity> Scene::GetMainCharacter() {
    return m_mainCharacter;
}

/*!
 * Returns the list of scenes.
 * 
 * @return the list of scenes which are file paths.
 */
std::vector<std::string>& Scene::getScenes() {
    return m_Scenes;
}