#ifndef ENGINE_HPP
#define ENGINE_HPP

#include <stdlib.h>
#include <time.h>

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "IGraphicsEngineRenderer.hpp"
#include "ResourceManager.hpp"
#include "SceneManager.hpp"
#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_sdlrenderer.h"

/**
 * This class sets up the main game engine
 */
class Engine {
   public:
    /**
     * Constructor of Engine
     */
    Engine();
    /**
     * Destructor
     */
    ~Engine();
    /**
     * Input engine
     */
    void Input(bool* quit);
    /**
     * Per frame update
     */
    void Update();
    /**
     * Per frame render. Renders everything
     */
    void Render(ImGuiIO& mIo);
    /**
     * Main Game Loop that runs forever
     */
    void MainGameLoop();
    /**
     * Initialization and shutdown pattern
     * Explicitly call 'Start' to launch the engine
     */
    void Start();
    /**
     * Initialization and shutdown pattern
     * Explicitly call 'Shutdown' to terminate the engine
     */
    void Shutdown();

    /**
     * Request to startup the Graphics Subsystem
     */
    int InitializeGraphicsSubSystem();

    /**
     * Request to startup the Resource Manager and load all images in directory
     */
    void InitializeResourceSubSystem();

    /**
     * Request to startup the Scene Manager and set scene renderer
     */
    void InitializeSceneManagerSubSystem();

   private:
    // Engine Subsystem
    // Setup the Graphics Rendering Engine
    IGraphicsEngineRenderer* mGraphicsEngineRenderer = nullptr;
    SDL_Window* mWindow;
    SDL_Renderer* mRenderer;
};

#endif
