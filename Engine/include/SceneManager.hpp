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

    void AddGameObject(GameObject& gameObject);

private:
	SceneManager();

    ~SceneManager();
    
    SceneManager(SceneManager const&);

    void operator=(SceneManager const&);
    
    std::vector<GameObject> mGameObjects;
    SDL_Renderer* mRenderer;
};


#endif
