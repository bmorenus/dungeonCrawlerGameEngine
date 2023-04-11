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
    mCollisionComponent = new CollisionComponent();
    std::cout << mRenderer << std::endl;
    mTileMap = new TileMap(ROWS, COLS, TILE_WIDTH, TILE_HEIGHT, MAP_X, MAP_Y);

    CharacterCreator* mainCharacterCreator =
        new CharacterCreator("main-character",
                             "images/sprites/linkSpriteImage.bmp",
                             TEMP_WIDTH,
                             TEMP_HEIGHT,
                             std::bind(&SceneManager::CreateMainCharacter,
                                       this,
                                       std::placeholders::_1,
                                       std::placeholders::_2,
                                       std::placeholders::_3,
                                       std::placeholders::_4));

    mCurrentCreator = mainCharacterCreator;

    CharacterCreator* groundTile =
        new CharacterCreator("ground-tile",
                             "images/tiles/ground.bmp",
                             TILE_WIDTH,
                             TILE_HEIGHT,
                             std::bind(&SceneManager::CreateMapTile,
                                       this,
                                       std::placeholders::_1,
                                       std::placeholders::_2,
                                       std::placeholders::_3,
                                       std::placeholders::_4));

    CharacterCreator* grassTile =
        new CharacterCreator("grass-tile",
                             "images/tiles/grass.bmp",
                             TILE_WIDTH,
                             TILE_HEIGHT,
                             std::bind(&SceneManager::CreateGrassMapTile,
                                       this,
                                       std::placeholders::_1,
                                       std::placeholders::_2,
                                       std::placeholders::_3,
                                       std::placeholders::_4));

    CharacterCreator* flowerTile =
        new CharacterCreator("flower-tile",
                             "images/tiles/flower.bmp",
                             TILE_WIDTH,
                             TILE_HEIGHT,
                             std::bind(&SceneManager::CreateMapTile,
                                       this,
                                       std::placeholders::_1,
                                       std::placeholders::_2,
                                       std::placeholders::_3,
                                       std::placeholders::_4));

    CharacterCreator* coinTile =
        new CharacterCreator("coin-tile",
                             "images/tiles/coin.bmp",
                             TILE_WIDTH,
                             TILE_HEIGHT,
                             std::bind(&SceneManager::CreateCoinMapTile,
                                       this,
                                       std::placeholders::_1,
                                       std::placeholders::_2,
                                       std::placeholders::_3,
                                       std::placeholders::_4));

    mCharacterCreators.push_back(groundTile);
    mCharacterCreators.push_back(grassTile);
    mCharacterCreators.push_back(flowerTile);
    mCharacterCreators.push_back(coinTile);
    mCharacterCreators.push_back(mainCharacterCreator);
}

void SceneManager::Shutdown() {
    for (GameObject* gameObject : mGameObjects) {
        delete gameObject;
    }
}

void SceneManager::AddGameObject(GameObject* gameObject) {
    mGameObjects.push_back(gameObject);
}

void SceneManager::CreateMainCharacter(int x, int y, int width, int height) {
    std::cout << "conrollting" << std::endl;
    ControllerComponent* controllerComponent = new ControllerComponent();
    TransformComponent* transformComponent = new TransformComponent();
    SpriteComponent* spriteComponent = CreateSpriteComponent(
        "./images/spritesheets/linkSprite.bmp");

    std::cout << "framing" << std::endl;
    AddTestFrameSequences(spriteComponent);
    GameObject* mainCharacter = CreateGameObject(x, y, width, height, 0);
    mainCharacter->AddComponent(controllerComponent);
    mainCharacter->AddComponent(transformComponent);
    mainCharacter->AddComponent(mCollisionComponent);
    mainCharacter->AddComponent(spriteComponent);

    std::cout << "colliding" << std::endl;
    PhysicsManager::GetInstance().AddCollisionObject(mainCharacter);
    AddGameObject(mainCharacter);
    std::cout << "completed" << std::endl;
}

void SceneManager::CreateMapTile(int x, int y, int width, int height) {
    int positionX = ((x - (x % width)) -
                     X_BORDER_PX_SIZE + (width / 2));
    int positionY = ((y - (y % height)) -
                     Y_BORDER_PX_SIZE + (height / 2));

    std::cout << "rcreating map tile" << std::endl;

    GameObject* gameObject = CreateGameObject(positionX,
                                              positionY,
                                              width,
                                              height,
                                              12);

    TileMapComponent* tmpTileMapComponent = CreateTileMapComponent(mCurrentCreator->imageFilePath);
    gameObject->AddComponent(tmpTileMapComponent);
    PhysicsManager::GetInstance().AddCollisionObject(gameObject);
    AddGameObject(gameObject);
}

void SceneManager::CreateGrassMapTile(int x, int y, int width, int height) {
    int positionX = ((x - (x % width)) -
                     X_BORDER_PX_SIZE + (width / 2));
    int positionY = ((y - (y % height)) -
                     Y_BORDER_PX_SIZE + (height / 2));

    std::cout << "rcreating map tile" << std::endl;

    GameObject* gameObject = CreateGameObject(positionX,
                                              positionY,
                                              width,
                                              height,
                                              12);

    TileMapComponent* tmpTileMapComponent = CreateTileMapComponent(mCurrentCreator->imageFilePath);
    gameObject->AddComponent(tmpTileMapComponent);
    gameObject->objectType = ObjectType::GRASS;
    PhysicsManager::GetInstance().AddCollisionObject(gameObject);
    AddGameObject(gameObject);
}

void SceneManager::CreateCoinMapTile(int x, int y, int width, int height) {
    int positionX = ((x - (x % width)) -
                     X_BORDER_PX_SIZE + (width / 2));
    int positionY = ((y - (y % height)) -
                     Y_BORDER_PX_SIZE + (height / 2));

    std::cout << "rcreating map tile" << std::endl;

    GameObject* gameObject = CreateGameObject(positionX,
                                              positionY,
                                              width,
                                              height,
                                              12);

    TileMapComponent* tmpTileMapComponent = CreateTileMapComponent(mCurrentCreator->imageFilePath);
    gameObject->AddComponent(tmpTileMapComponent);
    gameObject->objectType = ObjectType::COIN;
    PhysicsManager::GetInstance().AddCollisionObject(gameObject);
    AddGameObject(gameObject);
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
    CreateMainCharacter(100, 100, TEMP_WIDTH, TEMP_HEIGHT);
}

void SceneManager::AcceptInput(SDL_Event& e, ImVec2 screenEditorPos) {
    if (e.type == SDL_MOUSEBUTTONDOWN) {
        int x, y;
        SDL_GetMouseState(&x, &y);

        int screenPositionX = x - screenEditorPos.x;
        int screenPositionY = y - screenEditorPos.y;

        std::cout << mCurrentCreator->imageFilePath << std::endl;

        mCurrentCreator->creationFunction(screenPositionX,
                                          screenPositionY,
                                          mCurrentCreator->width,
                                          mCurrentCreator->height);
    }

    for (GameObject* gameObject : mGameObjects) {
        gameObject->AddEvent(e);
    }
}

void SceneManager::setCharacterCreator(CharacterCreator* characterCreator) {
    mCurrentCreator = characterCreator;
}

std::vector<CharacterCreator*> SceneManager::GetCharacterCreators() {
    return mCharacterCreators;
}

std::vector<CharacterCreator*> SceneManager::GetTileCreators() {
    return mTileCreators;
}

void SceneManager::Update() {
    for (GameObject* gameObject : mGameObjects) {
        gameObject->Update();
    }
}

void SceneManager::Render() {
    for (int i = mGameObjects.size() - 1; i >= 0; i--) {
        mGameObjects.at(i)->Render(mRenderer);
    }
}
