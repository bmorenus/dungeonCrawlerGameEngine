#ifndef SCENE_MANAGER_HPP
#define SCENE_MANAGER_HPP

#if defined(LINUX) || defined(MINGW)
#include <SDL2/SDL.h>
#else
#include <SDL.h>
#endif

#include <filesystem>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include "CoinCollisionComponent.hpp"
#include "CollisionComponent.hpp"
#include "ControllerComponent.hpp"
#include "GameObject.hpp"
#include "PhysicsManager.hpp"
#include "ResourceManager.hpp"
#include "SpriteComponent.hpp"
#include "TileMap.hpp"
#include "TileMapComponent.hpp"
#include "TransformComponent.hpp"
#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_sdlrenderer.h"

struct CharacterCreator {
    std::string characterName;
    std::string imageFilePath;
    int width;
    int height;
    std::function<void(int, int, int, int)> creationFunction;

    CharacterCreator(std::string _name,
                     std::string _filePath,
                     int _width,
                     int _height,
                     std::function<void(int, int, int, int)> _creationFunction) {
        characterName = _name;
        imageFilePath = _filePath;
        width = _width;
        height = _height;
        creationFunction = _creationFunction;
    }
};

class SceneManager {
   public:
    static SceneManager& GetInstance();

    void Initialize(SDL_Renderer* renderer);

    void AcceptInput(SDL_Event& e, ImVec2 screenEditorPos);

    void Render();

    void Update();

    void CreateComponentWrapper(const std::string& keyName, const std::string& componentType);

    void CreateGameObjectWrapper(const std::string& keyName, const std::string& objectType, int x, int y, int width, int height);
    
    void AddComponentWrapper(const std::string& gameObjectKeyName, const std::string& componentKeyName);

    void AddGameObjectWrapper(const std::string& gameObjectKeyName);

    void AddCollisionObjectWrapper(const std::string& gameObjectKeyName);

    GameObject* CreateGameObject(int xPos, int yPos, int width, int height, ObjectType type, int frame);

    TileMapComponent* CreateTileMapComponent(std::string spritesheetFile);

    SpriteComponent* CreateSpriteComponent(std::string spritesheetFile);

    void CreateMainCharacter(int x, int y, int width, int height);

    void CreateMapTile(int x, int y, int width, int height);

    void CreateGrassMapTile(int x, int y, int width, int height);

    void CreateCoinMapTile(int x, int y, int width, int height);

    void CreateMapTileWithType(int x, int y, int width, int height, ObjectType type, bool addCollision);

    void setCharacterCreator(CharacterCreator* mCurrentCreator);

    void AddTestFrameSequences(SpriteComponent* spriteComponent);

    void AddGameObject(GameObject* gameObject);

    std::vector<CharacterCreator*> GetCharacterCreators();

    std::vector<CharacterCreator*> GetTileCreators();

    void Shutdown();

    SDL_Texture* CreateTexture(std::string spritesheetFile);

   private:
    std::vector<GameObject*> mGameObjects;
    SDL_Renderer* mRenderer = nullptr;
    TileMap* mTileMap = nullptr;
    CollisionComponent* mCollisionComponent = nullptr;
    CharacterCreator* mCurrentCreator = nullptr;
    std::vector<CharacterCreator*> mCharacterCreators;
    std::vector<CharacterCreator*> mTileCreators;
    std::map<std::string, Component*> mComponentMap;
    std::map<std::string, GameObject*> mGameObjectMap;
};

#endif
