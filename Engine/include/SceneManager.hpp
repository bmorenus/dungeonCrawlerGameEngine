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
    std::function<GameObject*(int, int, int, int)> creationFunction;

    CharacterCreator(std::string _name,
                     std::string _filePath,
                     int _width,
                     int _height,
                     std::function<GameObject*(int, int, int, int)> _creationFunction) {
        characterName = _name;
        imageFilePath = _filePath;
        width = _width;
        height = _height;
        creationFunction = _creationFunction;
    }
};

class SceneManager {
   public:
    /*!
     * Returns the singleton instance of the SceneManager class for the game engine
     */
    static SceneManager& GetInstance();

    /*!
     * Performs all initializing functions for the SceneManager class
     */
    void Initialize(SDL_Renderer* renderer);

    /*!
     * Accepts the user input and acts on the provided input according
     */
    void AcceptInput(SDL_Event& e, ImVec2 screenEditorPos);

    /*!
     * Renders all renderable game objects found within the scene
     */
    void Render();

    /*!
     * Updates all game objects found within the scene
     */
    void Update();

    /*!
     * Wraps the given component by name / type to allow it to be accessed in the PyBind API
     */
    void CreateComponentWrapper(const std::string& keyName, const std::string& componentType);

    /*!
     * Wraps the given object by name / type to allow it to be accessed in the PyBind API
     */
    void CreateGameObjectWrapper(const std::string& keyName, const std::string& objectType, int x, int y, int width, int height);

    /*!
     * Adds the component wrapper by the given object by name / type to allow access to the component through the PyBind API
     */
    void AddComponentWrapper(const std::string& gameObjectKeyName, const std::string& componentKeyName);

    /*!
     * Adds the game object wrapper by the given object by name / type to allow access to the component through the PyBind API
     */
    void AddGameObjectWrapper(const std::string& gameObjectKeyName);

    /*!
     * Adds the colllision object wrapper by the given object key name to allow access to the component through the PyBind API
     */
    void AddCollisionObjectWrapper(const std::string& gameObjectKeyName);

    /*!
     * Creates function for a game objects that assigns the provided fields to the constructor of the game object
     */
    GameObject* CreateGameObject(int xPos, int yPos, int width, int height, ObjectType type, int frame, std::string tag);

    /*!
     * Creates a TileMap Component based on the provided sprite sheet file
     */
    TileMapComponent* CreateTileMapComponent(std::string spritesheetFile);

    /*!
     * Creates a Sprite Component based on the provided sprite sheet file
     */
    SpriteComponent* CreateSpriteComponent(std::string spritesheetFile);

    /*!
     * Creation function for the main character game object that assigns x, y, width, and height fields to the main character
     */
    GameObject* CreateMainCharacter(int x, int y, int width, int height);

    /*!
     * Creation function for the ground map tile game object that assigns x, y, width, and height fields to the tile
     */
    GameObject* CreateMapTile(int x, int y, int width, int height);

    /*!
     * Creation function for the grass map tile game object that assigns x, y, width, and height fields to the tile
     */
    GameObject* CreateGrassMapTile(int x, int y, int width, int height);

    /*!
     * Creation function for the coin map tile game object that assigns x, y, width, and height fields to the tile
     */
    GameObject* CreateCoinMapTile(int x, int y, int width, int height);

    /*!
     * Creation function for the flower map tile game object that assigns x, y, width, and height fields to the tile
     */
    GameObject* CreateFlowerMapTile(int x, int y, int width, int height);

    GameObject* CreateMapTileWithType(int x, int y, int width, int height, ObjectType type, bool addCollision);

    /*!
     * Sets the current character creator struct/function to use whenever a mouse click occurs
     */
    void setCharacterCreator(CharacterCreator* mCurrentCreator);

    /*!
     * Adds a frame sequence to the provided sprite component for animation
     */
    void AddTestFrameSequences(SpriteComponent* spriteComponent);

    /*!
     * Adds the provided game object to the current update / render loop for the scene
     */
    void AddGameObject(GameObject* gameObject);

    /*!
     * Returns the number of coins remaining in the scene
     */
    int GetNumberOfCoins();

    /*!
     * Converts the current game objects found in the scene and into a vector returns them with their respective x, y, width, height fields
     */
    std::vector<std::vector<std::string>> EncodeGameLevel();

    /*!
     * Converts the provided game level data from a vector into the corresponding game objects with their respective x, y, width, height fields
     */
    int BuildGameLevel(std::vector<std::vector<std::string>> gameLevelData);

    /*!
     * Returns the list of character creator structs to reference
     */
    std::vector<CharacterCreator*> GetCharacterCreators();

    /*!
     * Returns the list of tile creator structs to reference
     */
    std::vector<CharacterCreator*> GetTileCreators();

    /*!
     * Performs game engine shutdown actions for the SceneManager class
     */
    void Shutdown();

    /*!
     * Creates an SDL_Texture* based on the provided sprite sheet file
     */
    SDL_Texture* CreateTexture(std::string spritesheetFile);

   private:
    int numberOfCoins;
    std::vector<GameObject*> mGameObjects;
    SDL_Renderer* mRenderer = nullptr;
    TileMap* mTileMap = nullptr;
    CollisionComponent* mCollisionComponent = nullptr;
    CharacterCreator* mCurrentCreator = nullptr;
    std::vector<CharacterCreator*> mCharacterCreators;
    std::vector<CharacterCreator*> mTileCreators;
    std::unordered_map<std::string, CharacterCreator*> mCharacterCreatorsMap;
    std::map<std::string, Component*> mComponentMap;
    std::map<std::string, GameObject*> mGameObjectMap;
};

#endif
