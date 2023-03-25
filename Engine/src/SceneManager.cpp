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

void SceneManager::AddTestGameObjects() {
    ControllerComponent* controllerComponent = new ControllerComponent();
    TransformComponent* transformComponent = new TransformComponent();
    SpriteComponent* spriteComponent = new SpriteComponent();
    spriteComponent->LoadImage("./images/sprite.bmp", mRenderer);

    GameObject* testCharacter = new GameObject(mRenderer);
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
