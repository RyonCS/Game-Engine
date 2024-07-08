// TextureComponent.hpp
#include "TextureComponent.hpp"
#include "ResourceManager.hpp"
#include "TransformComponent.hpp"
#include "GameEntity.hpp"

TextureComponent::TextureComponent() {}

TextureComponent::~TextureComponent() {}

/*!
 * Creates a texture component by loading in a .bmp file.
 * 
 * @param renderer - Our renderer.
 * @param filePath - path to the .bmp file.
 */
void TextureComponent::CreateTextureComponent(SDL_Renderer* renderer, std::string filePath) {
    mTexture = ResourceManager::Instance().LoadTexture(renderer, filePath);
}

void TextureComponent::Input(float deltaTime) {}

void TextureComponent::Update(float deltaTime) { }

/*!
 * Renders the texture.
 * 
 * @param renderer - Our renderer.
 */
void TextureComponent::Render(SDL_Renderer* renderer){
    if (!renderer) {
            SDL_Log("Error with renderer in TextureComponent: %s\n", SDL_GetError());
            return; // Exit if window creation fails.
        }
    if(nullptr == mTexture) {
        auto ge = GetGameEntity();
        auto transform = ge->GetTransform()->GetRectangle();
        SDL_RenderDrawRect(renderer, &transform);
    } else {
        auto ge = GetGameEntity();
        auto transform = ge->GetTransform()->GetRectangle();
        int value = SDL_RenderCopy(renderer, mTexture.get(), nullptr, &transform);
    }
}

ComponentType TextureComponent::GetType() {
    return ComponentType::TextureComponent;
}
