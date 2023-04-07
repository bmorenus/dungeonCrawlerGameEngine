#include "SceneManager.hpp"

#include <iostream>
#include <string>

int ROWS = 8;
int COLS = 8;
int TILE_WIDTH = 32;
int TILE_HEIGHT = 32;
int MAP_X = 20;
int MAP_Y = 11;

int TEMP_WIDTH = 50;
int TEMP_HEIGHT = 50;

int X_BORDER_PX_SIZE = 9;
int Y_BORDER_PX_SIZE = 14;

SceneManager& SceneManager::GetInstance() {
    static SceneManager instance;
    return instance;
}

void SceneManager::Initialize(SDL_Renderer* renderer) {
    mRenderer = renderer;
}

void SceneManager::Shutdown() {
    for (GameObject* gameObject : mGameObjects) {
        delete gameObject;
    }
}

void SceneManager::AddGameObject(GameObject* gameObject) {
    mGameObjects.push_back(gameObject);
}

GameObject* SceneManager::CreateGameObject(int xPos, int yPos, int width,
                                           int height, int frame) {
    GameObject* gameObject = new GameObject(mRenderer, xPos, yPos, width,
                                            height, frame);
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

void SceneManager::AddTestFrameSequences(SpriteComponent* spriteComponent) {
    // Left Standing Frame
    Frame* left_standing = new Frame(1, 8, 22, 21, true);

    // Right Standing Frame
    Frame* right_standing = new Frame(1, 8, 22, 21, false);

    // Forward Standing Frame
    Frame* forward_standing = new Frame(49, 8, 22, 21, false);

    // Backward Standing Frame
    Frame* backward_standing = new Frame(73, 8, 22, 21, false);

    // Left Walking Frame
    Frame* left_walking = new Frame(25, 8, 22, 21, true);

    // Right Walking Frame
    Frame* right_walking = new Frame(25, 8, 22, 21, false);

    // Forward Walking Frame
    Frame* forward_walking = new Frame(49, 32, 22, 21, false);

    // Backward Walking Frame
    Frame* backward_walking = new Frame(73, 56, 22, 21, false);

    // Left Standing Sequence
    std::vector<Frame*> left_standing_sequence;
    left_standing_sequence.push_back(left_standing);
    spriteComponent->AddFrameSequence("left_standing", left_standing_sequence);

    // Right Standing Sequence
    std::vector<Frame*> right_standing_sequence;
    right_standing_sequence.push_back(right_standing);
    spriteComponent->AddFrameSequence("right_standing", right_standing_sequence);

    // Forward Standing Sequence
    std::vector<Frame*> forward_standing_sequence;
    forward_standing_sequence.push_back(forward_standing);
    spriteComponent->AddFrameSequence("forward_standing", forward_standing_sequence);

    // Backward Standing Sequence
    std::vector<Frame*> backward_standing_sequence;
    backward_standing_sequence.push_back(backward_standing);
    spriteComponent->AddFrameSequence("backward_standing", backward_standing_sequence);

    // Left Walking Sequence
    std::vector<Frame*> left_walking_sequence;
    left_walking_sequence.push_back(left_standing);
    left_walking_sequence.push_back(left_walking);
    spriteComponent->AddFrameSequence("left_walking", left_walking_sequence);

    // Right Walking Sequence
    std::vector<Frame*> right_walking_sequence;
    right_walking_sequence.push_back(right_standing);
    right_walking_sequence.push_back(right_walking);
    spriteComponent->AddFrameSequence("right_walking", right_walking_sequence);

    // Forward Walking Sequence
    std::vector<Frame*> forward_walking_sequence;
    forward_walking_sequence.push_back(forward_standing);
    forward_walking_sequence.push_back(forward_walking);
    spriteComponent->AddFrameSequence("forward_walking", forward_walking_sequence);

    // Backward Walking Sequence
    std::vector<Frame*> backward_walking_sequence;
    backward_walking_sequence.push_back(backward_standing);
    backward_walking_sequence.push_back(backward_walking);
    spriteComponent->AddFrameSequence("backward_walking", backward_walking_sequence);
}

void SceneManager::AddTestGameObjects() {
    ControllerComponent* controllerComponent = new ControllerComponent();
    TransformComponent* transformComponent = new TransformComponent();
    mCollisionComponent = new CollisionComponent();
    SpriteComponent* spriteComponent = CreateSpriteComponent(
        "./images/linkSprite.bmp");

    AddTestFrameSequences(spriteComponent);
    GameObject* testCharacter = CreateGameObject(100, 100, TEMP_WIDTH,
                                                 TEMP_HEIGHT, 0);

    testCharacter->AddComponent(controllerComponent);
    testCharacter->AddComponent(transformComponent);
    testCharacter->AddComponent(mCollisionComponent);
    testCharacter->AddComponent(spriteComponent);

    PhysicsManager::GetInstance().AddCollisionObject(testCharacter);
    AddGameObject(testCharacter);

    mTileMap = new TileMap(ROWS, COLS, TILE_WIDTH, TILE_HEIGHT, MAP_X, MAP_Y,
                           mRenderer);

    mTileMap->GenerateSimpleMap();
}

void SceneManager::AcceptInput(SDL_Event& e, ImVec2 screenEditorPos) {
    if (e.type == SDL_MOUSEBUTTONDOWN) {
        int x, y;
        SDL_GetMouseState(&x, &y);

        int screenPositionX = x - screenEditorPos.x;
        int screenPositionY = y - screenEditorPos.y;

        int positionX = ((screenPositionX - (screenPositionX % TILE_WIDTH)) -
                         X_BORDER_PX_SIZE + (TILE_WIDTH / 2));
        int positionY = ((screenPositionY - (screenPositionY % TILE_HEIGHT)) -
                         Y_BORDER_PX_SIZE + (TILE_HEIGHT / 2));

        GameObject* gameObject = CreateGameObject(positionX,
                                                  positionY,
                                                  TILE_WIDTH,
                                                  TILE_HEIGHT,
                                                  12);

        TileMapComponent* tmpTileMapComponent = CreateTileMapComponent(mTileFilePath);
        gameObject->AddComponent(tmpTileMapComponent);
        PhysicsManager::GetInstance().AddCollisionObject(gameObject);
        AddGameObject(gameObject);
    }

    for (GameObject* gameObject : mGameObjects) {
        gameObject->AddEvent(e);
    }
}

void SceneManager::setTilePath(std::string TileFilePath) {
    mTileFilePath = TileFilePath;
}

void SceneManager::Update() {
    for (GameObject* gameObject : mGameObjects) {
        gameObject->Update();
    }
}

void SceneManager::Render() {
    for (GameObject* gameObject : mGameObjects) {
        gameObject->Render(mRenderer);
    }
}
