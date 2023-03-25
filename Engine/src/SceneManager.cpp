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
    static SceneManager* sInstance = new SceneManager;
    return *sInstance;
}

void SceneManager::Initialize(SDL_Renderer* renderer) {
    mRenderer = renderer;
}

void SceneManager::AddGameObject(GameObject& gameObject) {
    mGameObjects.push_back(gameObject);
}
