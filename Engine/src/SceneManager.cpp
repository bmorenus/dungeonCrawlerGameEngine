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

    numberOfCoins = 0;
    mCollisionComponent = new CollisionComponent();
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
                             std::bind(&SceneManager::CreateFlowerMapTile,
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

    mCharacterCreatorsMap.insert({"main-character", mainCharacterCreator});
    mCharacterCreatorsMap.insert({"ground-tile", groundTile});
    mCharacterCreatorsMap.insert({"grass-tile", grassTile});
    mCharacterCreatorsMap.insert({"flower-tile", flowerTile});
    mCharacterCreatorsMap.insert({"coin-tile", coinTile});
}

void SceneManager::Shutdown() {
    for (GameObject* gameObject : mGameObjects) {
        delete gameObject;
    }
}

void SceneManager::AddGameObject(GameObject* gameObject) {
    mGameObjects.push_back(gameObject);
}

void SceneManager::CreateComponentWrapper(const std::string& keyName, const std::string& componentType) {
    Component* component;

    if (componentType == "CONTROLLER") {
        component = new ControllerComponent();
    } else if (componentType == "TRANSFORM") {
        component = new TransformComponent();
    } else if (componentType == "SPRITE") {
        SpriteComponent* spriteComponent = CreateSpriteComponent("./images/spritesheets/linkSprite.bmp");
        AddTestFrameSequences(spriteComponent);
        component = spriteComponent;
    } else if (componentType == "COLLISION") {
        component = mCollisionComponent;
    } else {
        return;
    }

    mComponentMap[keyName] = component;
}

void SceneManager::CreateGameObjectWrapper(const std::string& keyName,
                                           const std::string& objectType,
                                           int x,
                                           int y,
                                           int width,
                                           int height) {
    GameObject* gameObject;

    if (objectType == "DEFAULT") {
        gameObject = CreateGameObject(x, y, width, height, ObjectType::DEFAULT, 0, "main-character");
    } else if (objectType == "BLOCKABLE_TILE") {
        std::cout << "test" << std::endl;
        gameObject = CreateGameObject(x, y, width, height, ObjectType::BLOCKABLE_TILE, 12, "ground-tile");
    } else if (objectType == "PASSABLE_TILE") {
        gameObject = CreateGameObject(x, y, width, height, ObjectType::PASSABLE_TILE, 12, "flower-tile");
    } else if (objectType == "COIN") {
        gameObject = CreateGameObject(x, y, width, height, ObjectType::COIN, 12, "coin-tile");
    } else {
        return;
    }

    mGameObjectMap[keyName] = gameObject;
}

void SceneManager::AddComponentWrapper(const std::string& gameObjectKeyName, const std::string& componentKeyName) {
    mGameObjectMap[gameObjectKeyName]->AddComponent(mComponentMap[componentKeyName]);
}

void SceneManager::AddGameObjectWrapper(const std::string& gameObjectKeyName) {
    mGameObjects.push_back(mGameObjectMap[gameObjectKeyName]);
}

void SceneManager::AddCollisionObjectWrapper(const std::string& gameObjectKeyName) {
    PhysicsManager::GetInstance().AddCollisionObject(mGameObjectMap[gameObjectKeyName]);
}

GameObject* SceneManager::CreateMainCharacter(int x, int y, int width, int height) {
    ControllerComponent* controllerComponent = new ControllerComponent();
    TransformComponent* transformComponent = new TransformComponent();
    SpriteComponent* spriteComponent = CreateSpriteComponent(
        "./images/spritesheets/linkSprite.bmp");

    AddTestFrameSequences(spriteComponent);
    GameObject* mainCharacter = CreateGameObject(x,
                                                 y,
                                                 width,
                                                 height,
                                                 ObjectType::DEFAULT,
                                                 0,
                                                 "main-character");
    mainCharacter->AddComponent(controllerComponent);
    mainCharacter->AddComponent(transformComponent);
    mainCharacter->AddComponent(mCollisionComponent);
    mainCharacter->AddComponent(spriteComponent);

    PhysicsManager::GetInstance().AddCollisionObject(mainCharacter);
    return mainCharacter;
}

GameObject* SceneManager::CreateMapTile(int x, int y, int width, int height) {
    int positionX = ((x - (x % width)) -
                     X_BORDER_PX_SIZE + (width / 2));
    int positionY = ((y - (y % height)) -
                     Y_BORDER_PX_SIZE + (height / 2));

    GameObject* gameObject = CreateGameObject(positionX,
                                              positionY,
                                              width,
                                              height,
                                              ObjectType::BLOCKABLE_TILE,
                                              12,
                                              "ground-tile");

    TileMapComponent* tmpTileMapComponent = CreateTileMapComponent(mCurrentCreator->imageFilePath);
    gameObject->AddComponent(tmpTileMapComponent);
    PhysicsManager::GetInstance().AddCollisionObject(gameObject);
    return gameObject;
}

GameObject* SceneManager::CreateGrassMapTile(int x, int y, int width, int height) {
    int positionX = ((x - (x % width)) -
                     X_BORDER_PX_SIZE + (width / 2));
    int positionY = ((y - (y % height)) -
                     Y_BORDER_PX_SIZE + (height / 2));

    std::cout << "test tile" << std::endl;

    GameObject* gameObject = CreateGameObject(positionX,
                                              positionY,
                                              width,
                                              height,
                                              ObjectType::PASSABLE_TILE,
                                              12,
                                              "grass-tile");

    TileMapComponent* tmpTileMapComponent = CreateTileMapComponent("./images/tiles/grass.bmp");
    gameObject->AddComponent(tmpTileMapComponent);
    return gameObject;
}

GameObject* SceneManager::CreateCoinMapTile(int x, int y, int width, int height) {
    int positionX = ((x - (x % width)) -
                     X_BORDER_PX_SIZE + (width / 2));
    int positionY = ((y - (y % height)) -
                     Y_BORDER_PX_SIZE + (height / 2));

    GameObject* gameObject = CreateGameObject(positionX,
                                              positionY,
                                              width,
                                              height,
                                              ObjectType::COIN,
                                              12,
                                              "coin-tile");

    TileMapComponent* tmpTileMapComponent = CreateTileMapComponent("./images/tiles/coin.bmp");
    CoinCollisionComponent* coinCollisionComponent = new CoinCollisionComponent();
    gameObject->AddComponent(tmpTileMapComponent);
    gameObject->AddComponent(coinCollisionComponent);
    PhysicsManager::GetInstance().AddCollisionObject(gameObject);
    return gameObject;
}

GameObject* SceneManager::CreateFlowerMapTile(int x, int y, int width, int height) {
    int positionX = ((x - (x % width)) -
                     X_BORDER_PX_SIZE + (width / 2));
    int positionY = ((y - (y % height)) -
                     Y_BORDER_PX_SIZE + (height / 2));

    GameObject* gameObject = CreateGameObject(positionX,
                                              positionY,
                                              width,
                                              height,
                                              ObjectType::PASSABLE_TILE,
                                              12,
                                              "flower-tile");

    TileMapComponent* tmpTileMapComponent = CreateTileMapComponent("./images/tiles/flower.bmp");
    gameObject->AddComponent(tmpTileMapComponent);
    return gameObject;
}

GameObject* SceneManager::CreateGameObject(int xPos, int yPos, int width,
                                           int height, ObjectType type,
                                           int frame, std::string tag) {
    GameObject* gameObject = new GameObject(mRenderer, xPos, yPos, width,
                                            height, type, frame, tag);
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
        SDL_Texture* texture = SDL_CreateTextureFromSurface(mRenderer, sdlSurface);
        return texture;
    }
    return nullptr;
}

void SceneManager::AddTestFrameSequences(SpriteComponent* spriteComponent) {
    // Standing Frames
    Frame* left_standing = new Frame(1, 8, 22, 21, true);
    Frame* right_standing = new Frame(1, 8, 22, 21, false);
    Frame* forward_standing = new Frame(49, 8, 22, 21, false);
    Frame* backward_standing = new Frame(73, 8, 22, 21, false);

    // Walking Frames
    Frame* left_walking = new Frame(25, 8, 22, 21, true);
    Frame* right_walking = new Frame(25, 8, 22, 21, false);
    Frame* forward_walking = new Frame(49, 32, 22, 21, false);
    Frame* backward_walking = new Frame(73, 56, 22, 21, false);

    // Frame Sequences
    std::vector<Frame*> left_sequence{left_standing, left_walking};
    std::vector<Frame*> right_sequence{right_standing, right_walking};
    std::vector<Frame*> forward_sequence{forward_standing, forward_walking};
    std::vector<Frame*> backward_sequence{backward_standing, backward_walking};

    // Add frame sequences
    spriteComponent->AddFrameSequence("left_standing", {left_standing});
    spriteComponent->AddFrameSequence("right_standing", {right_standing});
    spriteComponent->AddFrameSequence("forward_standing", {forward_standing});
    spriteComponent->AddFrameSequence("backward_standing", {backward_standing});
    spriteComponent->AddFrameSequence("left_walking", left_sequence);
    spriteComponent->AddFrameSequence("right_walking", right_sequence);
    spriteComponent->AddFrameSequence("forward_walking", forward_sequence);
    spriteComponent->AddFrameSequence("backward_walking", backward_sequence);
}

int SceneManager::GetNumberOfCoins() {
    return numberOfCoins;
}

void SceneManager::AcceptInput(SDL_Event& e, ImVec2 screenEditorPos) {
    if (e.type == SDL_MOUSEBUTTONDOWN) {
        int x, y;
        SDL_GetMouseState(&x, &y);

        int screenPositionX = x - screenEditorPos.x;
        int screenPositionY = y - screenEditorPos.y;

        if ((0 > screenPositionX || screenPositionX > 640) ||
            (0 > screenPositionY || screenPositionY > 360)) {
            return;
        }

        std::cout << mCurrentCreator->imageFilePath << std::endl;
        std::cout << mCurrentCreator->characterName << std::endl;

        GameObject* gameObject = mCurrentCreator->creationFunction(screenPositionX,
                                                                   screenPositionY,
                                                                   mCurrentCreator->width,
                                                                   mCurrentCreator->height);

        AddGameObject(gameObject);
        return;
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

std::vector<std::vector<std::string>> SceneManager::EncodeGameLevel() {
    std::vector<std::vector<std::string>> gameLevelData;

    for (GameObject* gameObject : mGameObjects) {
        std::vector<std::string> gameObjectData;

        gameObjectData.push_back(gameObject->GetTag());
        gameObjectData.push_back(std::to_string(gameObject->GetX()));
        gameObjectData.push_back(std::to_string(gameObject->GetY()));
        gameObjectData.push_back(std::to_string(gameObject->GetWidth()));
        gameObjectData.push_back(std::to_string(gameObject->GetHeight()));

        gameLevelData.push_back(gameObjectData);
    }
    return gameLevelData;
}

int SceneManager::BuildGameLevel(std::vector<std::vector<std::string>> gameLevelData) {
    mGameObjects.clear();
    int count = 0;
    PhysicsManager::GetInstance().ClearCollisionObjects();

    for (std::vector<std::string> gameObjectData : gameLevelData) {
        std::string gameObjectTag = gameObjectData.at(0);

        std::unordered_map<std::string, CharacterCreator*>::iterator it;
        it = mCharacterCreatorsMap.find(gameObjectTag);

        if (it != mCharacterCreatorsMap.end()) {
            int xPos = stoi(gameObjectData.at(1));
            int yPos = stoi(gameObjectData.at(2));
            int width = stoi(gameObjectData.at(3));
            int height = stoi(gameObjectData.at(4));

            CharacterCreator* creator = it->second;
            GameObject* gameObject = creator->creationFunction(xPos, yPos, width, height);
            AddGameObject(gameObject);
        } else {
            return 1;
        }
    }
    return 0;
}

void SceneManager::Update() {
    int count = 0;
    for (auto it = mGameObjects.begin(); it != mGameObjects.end();) {
        GameObject* gameObject = *it;
        if (!gameObject->GetIsDeleted()) {
            gameObject->Update();
            ++it;
            if (gameObject->GetObjectType() == ObjectType::COIN) {
                count++;
            }
        } else {
            delete gameObject;
            it = mGameObjects.erase(it);
        }
    }
    numberOfCoins = count;
}

void SceneManager::Render() {
    for (int i = mGameObjects.size() - 1; i >= 0; i--) {
        mGameObjects.at(i)->Render();
    }
}
