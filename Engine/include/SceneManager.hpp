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
#include "TileMapComponent.hpp"
#include "TransformComponent.hpp"
#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_sdlrenderer.h"

class SceneManager {
   public:
    static SceneManager& GetInstance();

    void Initialize(SDL_Renderer* renderer);

    void AcceptInput(SDL_Event& e, ImVec2 screenEditorPos);

    void Render();

    void Update();

    GameObject* CreateGameObject(int xPos, int yPos, int frame);

    TileMapComponent* CreateTileMapComponent(std::string spritesheetFile);

    SpriteComponent* CreateSpriteComponent(std::string spritesheetFile);

    void AddTestGameObjects();

    void AddGameObject(GameObject* gameObject);

    void Shutdown();

   private:
    SceneManager();

    ~SceneManager();

    SceneManager(SceneManager const&);

    void operator=(SceneManager const&);

    SDL_Texture* CreateTexture(std::string spritesheetFile);

    std::vector<GameObject*> mGameObjects;
    SDL_Renderer* mRenderer = nullptr;
    TileMap* mTileMap = nullptr;
    TileMapComponent* mTileMapComponent = nullptr;
};

#endif
