#include "SceneManager.hpp"

#include <iostream>
#include <string>

int ROWS = 8;
int COLS = 8;
int TILE_WIDTH = 32;
int TILE_HEIGHT = 32;
int MAP_X = 20;
int MAP_Y = 11;

SceneManager::SceneManager() {
    std::cout << "Scene Manager Created" << std::endl;
}

SceneManager::SceneManager(SceneManager const&) {
}

SceneManager::~SceneManager() {
    std::cout << "Scene Manager Destroyed" << std::endl;
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
    delete mTileMapComponent;

    for (GameObject* gameObject : mGameObjects) {
        delete gameObject;
    }
}

void SceneManager::AddGameObject(GameObject* gameObject) {
    mGameObjects.push_back(gameObject);
}

GameObject* SceneManager::CreateGameObject(int xPos, int yPos, int frame) {
    GameObject* gameObject = new GameObject(mRenderer, xPos, yPos, frame);
    return gameObject;
}

SpriteComponent* SceneManager::CreateSpriteComponent(std::string spritesheetFile) {
    SDL_Texture* texture = CreateTexture(spritesheetFile);
    SpriteComponent* spriteComponent = new SpriteComponent(texture);
    return spriteComponent;
}

TileMapComponent* SceneManager::CreateTileMapComponent(std::string spritesheetFile) {
    SDL_Texture* texture = CreateTexture(spritesheetFile);
    TileMapComponent* tileMapComponent = new TileMapComponent(texture,
                                                              mTileMap);
    return tileMapComponent;
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
    SpriteComponent* spriteComponent = CreateSpriteComponent(
        "./images/sprite.bmp");

    GameObject* testCharacter = CreateGameObject(100, 100, 0);
    testCharacter->AddComponent(controllerComponent);
    testCharacter->AddComponent(transformComponent);
    testCharacter->AddComponent(spriteComponent);

    AddGameObject(testCharacter);

    mTileMap = new TileMap(ROWS, COLS, TILE_WIDTH, TILE_HEIGHT, MAP_X, MAP_Y,
                           mRenderer);

    mTileMap->GenerateSimpleMap();

    mTileMapComponent = CreateTileMapComponent("./images/Tiles1.bmp");

    for (int yPos = 0; yPos < MAP_Y; yPos++) {
        for (int xPos = 0; xPos < MAP_X; xPos++) {
            int currentTile = mTileMap->GetTileType(xPos, yPos);
            if (currentTile > -1) {
                GameObject* gameObject = CreateGameObject(xPos * TILE_WIDTH,
                                                          yPos * TILE_HEIGHT,
                                                          currentTile);
                gameObject->AddComponent(mTileMapComponent);
                AddGameObject(gameObject);
            }
        }
    }
}

void SceneManager::AcceptInput(SDL_Event& e) {
    for (GameObject* gameObject : mGameObjects) {
        gameObject->AddEvent(e);
    }
}

void SceneManager::Update() {
    static int frame = 0;
    frame++;
    if (frame > 6) {
        frame = 0;
    }

    for (GameObject* gameObject : mGameObjects) {
        gameObject->Update(frame);
    }
}

void SceneManager::Render() {
    for (GameObject* gameObject : mGameObjects) {
        gameObject->Render(mRenderer);
    }
}
