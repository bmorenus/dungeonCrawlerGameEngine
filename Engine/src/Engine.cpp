#include "Engine.hpp"
#include <map>
#include <string>
#include <memory>
#include <iterator>

#define CHARACTERS 1

GameObject* character;

TileMap* myTileMap;

Engine::Engine(){
}

Engine::~Engine(){
}

void Engine::Input(bool *quit){
    SDL_Event e;
    SDL_StartTextInput();
      while(SDL_PollEvent( &e ) != 0){
        if(e.type == SDL_QUIT){
          *quit = true;
        }
        character->AddEvent(e);
      }
}

void Engine::Update()
{
    static int frame = 0;
    frame++;
    if(frame>6){
        frame=0;
    }
    
    character->Update(frame);
}

void Engine::Render(){
    mRenderer->SetRenderDrawColor(110, 130,170,0xFF);
    mRenderer->RenderClear();
    SDL_Renderer* renderer = dynamic_cast<SDLGraphicsEngineRenderer*>(mRenderer)->GetRenderer();
    character->Render(renderer);
    myTileMap->Render(renderer);
    mRenderer->RenderPresent();
}

void Engine::MainGameLoop(){
    bool quit = false;

    while(!quit){
      Input(&quit);
      SDL_Delay(250); // Frame capping hack
      Update();
      Render();
    }
    SDL_StopTextInput();
}

void Engine::Start(){
    if(mRenderer!=nullptr){
        std::cout << "Initializing Graphics Subsystem\n";
    }else{
        std::cout << "No Graphics Subsystem initialized\n";
    }

    SDL_Renderer* renderer  = dynamic_cast<SDLGraphicsEngineRenderer*>(mRenderer)->GetRenderer();
    ControllerComponent* controllerComponent = new ControllerComponent();
    TransformComponent* transformComponent = new TransformComponent();
    SpriteComponent* spriteComponent = new SpriteComponent();
    spriteComponent->LoadImage("./images/sprite.bmp", renderer);

    character = new GameObject(renderer);
    character->AddComponent(controllerComponent);
    character->AddComponent(transformComponent);
    character->AddComponent(spriteComponent);

    myTileMap = new TileMap("./images/Tiles1.bmp",8,8,64,64,20,11,renderer);
    myTileMap->GenerateSimpleMap();
    myTileMap->PrintMap();

}

void Engine::Shutdown(){
    if(nullptr!=mRenderer){
        delete mRenderer;
    } 

    if(nullptr!=myTileMap){
        delete myTileMap;
    }

    delete character;
}

void Engine::InitializeGraphicsSubSystem(){
    mRenderer = new SDLGraphicsEngineRenderer(1280,720);
    if(nullptr == mRenderer){
        exit(1);
    }
}

void Engine::InitializeResourceSubSystem(){
    std::string imageDirPath = "images/";
    ResourceManager::GetInstance().Initialize(imageDirPath);
}

void Engine::InitializeSceneManagerSubSystem(){
    SceneManager::GetInstance().Initialize(
        dynamic_cast<SDLGraphicsEngineRenderer*>(mRenderer)->GetRenderer());
}
