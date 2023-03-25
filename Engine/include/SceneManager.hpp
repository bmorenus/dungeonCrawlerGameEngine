#ifndef SCENE_MANAGER_HPP
#define SCENE_MANAGER_HPP

#if defined(LINUX) || defined(MINGW)
    #include <SDL2/SDL.h>
#else 
    #include <SDL.h>
#endif

#include "GameObject.hpp"
#include "SpriteComponent.hpp"
#include "TransformComponent.hpp"
#include "ControllerComponent.hpp"
#include "TileMap.hpp"

#include <vector>
#include <string>

class SceneManager{

public:
    static SceneManager& GetInstance();

    void Initialize(SDL_Renderer* renderer);

    void AcceptInput(SDL_Event& e);

    void Render();

    void Update();

    void AddTestGameObjects();

    void AddDynamicGameObject(GameObject* gameObject);

    void AddStaticGameObject(TileMap* tileMap);

    void Shutdown();

private:
	SceneManager();

    ~SceneManager();
    
    SceneManager(SceneManager const&);

    void operator=(SceneManager const&);
    
    std::vector<GameObject*> mDynamicGameObjects;
    std::vector<TileMap*> mStaticGameObjects;
    SDL_Renderer* mRenderer = nullptr;
};


#endif
