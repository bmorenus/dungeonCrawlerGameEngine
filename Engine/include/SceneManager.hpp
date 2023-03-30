#ifndef SCENE_MANAGER_HPP
#define SCENE_MANAGER_HPP

#if defined(LINUX) || defined(MINGW)
#include <SDL2/SDL.h>
#else
#include <SDL.h>
#endif

#include <string>
#include <vector>

#include "ControllerComponent.hpp"
#include "GameObject.hpp"
#include "ResourceManager.hpp"
#include "SpriteComponent.hpp"
#include "TileMap.hpp"
#include "TransformComponent.hpp"

class SceneManager {
   public:
    static SceneManager& GetInstance();

    void Initialize(SDL_Renderer* renderer);

    void AcceptInput(SDL_Event& e);

    void Render();

    void Update();

    GameObject* CreateGameObject();

    SpriteComponent* CreateSpriteComponent(std::string spritesheetFile);

    void AddTestGameObjects();

    void AddDynamicGameObject(GameObject* gameObject);

    void AddStaticGameObject(TileMap* tileMap);

    void Shutdown();

   private:
    SceneManager();

    ~SceneManager();

    SceneManager(SceneManager const&);

    void operator=(SceneManager const&);

    SDL_Texture* CreateTexture(std::string spritesheetFile);

    std::vector<GameObject*> mDynamicGameObjects;
    std::vector<TileMap*> mStaticGameObjects;
    SDL_Renderer* mRenderer = nullptr;
};

#endif
