#include "SceneManager.hpp"
#include <iostream>
#include <string>

SceneManager::SceneManager(){
    std::cout << "Scene Manager Created" << std::endl;
}

SceneManager::SceneManager(SceneManager const&){
}

SceneManager::~SceneManager(){
    std::cout << "Scene Manager Destroyed" <<  std::endl; 
}

SceneManager& SceneManager::GetInstance() {
    static SceneManager* sInstance = new SceneManager();
    return *sInstance;
}

void SceneManager::Initialize(SDL_Renderer* renderer) {
    mRenderer = renderer;
    AddTestGameObjects();
}

void SceneManager::Shutdown() {
    for (GameObject* gameObject : mDynamicGameObjects) {
        delete gameObject;
    }

    for (TileMap* tileMap : mStaticGameObjects) {
        delete tileMap;
    }
}

void SceneManager::AddDynamicGameObject(GameObject* gameObject) {
    mDynamicGameObjects.push_back(gameObject);
}

void SceneManager::AddStaticGameObject(TileMap* tileMap) {
    mStaticGameObjects.push_back(tileMap);
}

GameObject* SceneManager::CreateGameObject() {
    GameObject* gameObject = new GameObject(mRenderer);
    return gameObject;
}

SpriteComponent* SceneManager::CreateSpriteComponent(std::string spritesheetFile) {
    SDL_Texture* texture = CreateTexture(spritesheetFile);
    SpriteComponent* spriteComponent = new SpriteComponent(texture);
    return spriteComponent;
}

SDL_Texture* SceneManager::CreateTexture(std::string spritesheetFile) {
    ResourceManager::GetInstance().LoadResource(spritesheetFile);
    SDL_Surface* sdlSurface = ResourceManager::GetInstance().GetResource(spritesheetFile).get();
    if (nullptr == sdlSurface) {
        SDL_Log("Failed to allocate surface");
    } else {
        SDL_Log("Allocated a bunch of memory to create identical game character");
        SDL_Texture* texture = SDL_CreateTextureFromSurface(mRenderer, sdlSurface);
        return texture;
    }
    return nullptr;
}

void SceneManager::AddTestGameObjects() {
    ControllerComponent* controllerComponent = new ControllerComponent();
    TransformComponent* transformComponent = new TransformComponent();
    SpriteComponent* spriteComponent = CreateSpriteComponent("images/sprite.bmp");

    GameObject* testCharacter = CreateGameObject();
    testCharacter->AddComponent(controllerComponent);
    testCharacter->AddComponent(transformComponent);
    testCharacter->AddComponent(spriteComponent);

    AddDynamicGameObject(testCharacter);

    TileMap* testTileMap = new TileMap("./images/Tiles1.bmp",8,8,64,64,20,11,mRenderer);
    testTileMap->GenerateSimpleMap();

    AddStaticGameObject(testTileMap);
}

void SceneManager::AcceptInput(SDL_Event& e) {
    for (GameObject* gameObject : mDynamicGameObjects) {
        gameObject->AddEvent(e);
    }
}

void SceneManager::Update() {
    static int frame = 0;
    frame++;
    if(frame>6){
        frame=0;
    }
    
    for (GameObject* gameObject : mDynamicGameObjects) {
        gameObject->Update(frame);
    }
}

void SceneManager::Render() {
    for (GameObject* gameObject : mDynamicGameObjects) {
        gameObject->Render(mRenderer);
    }

    for (TileMap* tileMap : mStaticGameObjects) {
        tileMap->Render(mRenderer);
    }
}
