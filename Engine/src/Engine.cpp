#include "Engine.hpp"
#include <map>
#include <string>
#include <memory>
#include <iterator>

Engine::Engine(){
}

Engine::~Engine(){
}

void Engine::Input(bool *quit){
    SDL_Event e;
    SDL_StartTextInput();
    while(SDL_PollEvent( &e ) != 0) {
        if(e.type == SDL_QUIT){
            *quit = true;
        }
        SceneManager::GetInstance().AcceptInput(e);
    }
}

void Engine::Update() {
    SceneManager::GetInstance().Update();
}

void Engine::Render(){
    mGraphicsEngineRenderer->SetRenderDrawColor(110, 130, 170, 0xFF);
    mGraphicsEngineRenderer->RenderClear();
    SceneManager::GetInstance().Render();
    mGraphicsEngineRenderer->RenderPresent();
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
    if(mGraphicsEngineRenderer!=nullptr){
        std::cout << "Initializing Graphics Subsystem\n";
    }else{
        std::cout << "No Graphics Subsystem initialized\n";
    }
}

void Engine::Shutdown(){
    if(nullptr!=mGraphicsEngineRenderer){
        delete mGraphicsEngineRenderer;
    } 
    SceneManager::GetInstance().Shutdown();
}

void Engine::InitializeGraphicsSubSystem(){
    mGraphicsEngineRenderer = new SDLGraphicsEngineRenderer(1280,720);
    if(nullptr == mGraphicsEngineRenderer){
        exit(1);
    }
}

void Engine::InitializeResourceSubSystem(){
    std::string imageDirPath = "images/";
    ResourceManager::GetInstance().Initialize(imageDirPath);
}

void Engine::InitializeSceneManagerSubSystem(){
    SceneManager::GetInstance().Initialize(
        dynamic_cast<SDLGraphicsEngineRenderer*>(mGraphicsEngineRenderer)->GetRenderer());
}
