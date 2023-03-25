#include "SceneManager.hpp"
#include <iostream>
#include <string>

SceneManager::SceneManager(){
    std::cout << "Created" << std::endl;
}

SceneManager::SceneManager(SceneManager const&){
}

SceneManager::~SceneManager(){
    std::cout << "Destroyed" <<  std::endl; 
}

SceneManager& SceneManager::GetInstance() {
    static SceneManager* s_instance = new SceneManager;
    return *s_instance;
}

void SceneManager::Initialize(SDL_Renderer* renderer) {
    mRenderer = renderer;
}

void SceneManager::AddGameObject(GameObject& gameObject) {
    mGameObjects.push_back(gameObject);
}
