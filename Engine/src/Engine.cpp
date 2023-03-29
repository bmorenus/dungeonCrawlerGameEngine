#include "Engine.hpp"

#include <iterator>
#include <map>
#include <memory>
#include <string>

bool show_demo_window = true;
bool show_another_window = false;
ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

Engine::Engine() {
}

Engine::~Engine() {
}

void Engine::Input(bool* quit) {
    SDL_Event e;
    SDL_StartTextInput();
    while (SDL_PollEvent(&e) != 0) {
        ImGui_ImplSDL2_ProcessEvent(&e);

        if (e.type == SDL_QUIT) {
            *quit = true;
        }
        if (e.type == SDL_WINDOWEVENT && e.window.event == SDL_WINDOWEVENT_CLOSE && e.window.windowID == SDL_GetWindowID(mWindow)) {
            *quit = true;
        }

        SceneManager::GetInstance().AcceptInput(e);
    }
}

void Engine::Update() {
    SceneManager::GetInstance().Update();
}

void Engine::Render(ImGuiIO& mIo) {
    // Start the Dear ImGui frame
    ImGui_ImplSDLRenderer_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    SceneManager::GetInstance().Render();
    ImGui::NewFrame();
    if (show_demo_window)
        ImGui::ShowDemoWindow(&show_demo_window);

    {
        ImGui::Begin("Scene Editor");
        ImGui::Image(mScreenTexture, ImVec2(640, 360));
        ImGui::End();
    }
    SDL_SetRenderTarget(mRenderer, NULL);

    // Rendering
    ImGui::Render();
    SDL_RenderSetScale(mRenderer, mIo.DisplayFramebufferScale.x, mIo.DisplayFramebufferScale.y);
    SDL_SetRenderDrawColor(mRenderer, (Uint8)(clear_color.x * 255), (Uint8)(clear_color.y * 255), (Uint8)(clear_color.z * 255), (Uint8)(clear_color.w * 255));
    SDL_RenderClear(mRenderer);
    ImGui_ImplSDLRenderer_RenderDrawData(ImGui::GetDrawData());
    SDL_RenderPresent(mRenderer);
}

void Engine::MainGameLoop() {
    bool quit = false;

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& mIo = ImGui::GetIO();
    (void)mIo;
    mIo.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;  // Enable Keyboard Controls
    mIo.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;   // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    // ImGui::StyleColorsLight();

    // Setup Platform/Renderer backends
    ImGui_ImplSDL2_InitForSDLRenderer(mWindow, mRenderer);
    ImGui_ImplSDLRenderer_Init(mRenderer);

    while (!quit) {
        Input(&quit);
        SDL_Delay(100);  // Frame capping hack
        Update();
        Render(mIo);
    }
    // SDL_StopTextInput();
}

void Engine::Start() {
    if (mRenderer != nullptr) {
        std::cout << "Initializing Graphics Subsystem\n";
    } else {
        std::cout << "No Graphics Subsystem initialized\n";
    }
}

void Engine::Shutdown() {
    if (nullptr != mGraphicsEngineRenderer) {
        delete mGraphicsEngineRenderer;
    }
    // SceneManager::GetInstance().Shutdown();
    // Cleanup
    ImGui_ImplSDLRenderer_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();

    SDL_DestroyRenderer(mRenderer);
    SDL_DestroyWindow(mWindow);
    SDL_Quit();
}

int Engine::InitializeGraphicsSubSystem() {
    mGraphicsEngineRenderer = new SDLGraphicsEngineRenderer(1280, 720);
    if (nullptr == mGraphicsEngineRenderer) {
        exit(1);
    }
    // Setup SDL
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER) != 0) {
        printf("Error: %s\n", SDL_GetError());
        return -1;
    }

    // From 2.0.18: Enable native IME.
#ifdef SDL_HINT_IME_SHOW_UI
    SDL_SetHint(SDL_HINT_IME_SHOW_UI, "1");
#endif

    // Create window with SDL_Renderer graphics context
    SDL_WindowFlags window_flags = (SDL_WindowFlags)(SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);
    mWindow = SDL_CreateWindow("Dear ImGui SDL2+SDL_Renderer example", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, window_flags);
    mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
    mScreenTexture = SDL_CreateTexture(mRenderer, SDL_PIXELFORMAT_ABGR8888, SDL_TEXTUREACCESS_TARGET, 640, 360);
    if (mRenderer == NULL) {
        SDL_Log("Error creating SDL_Renderer!");
        return 0;
    }
}

void Engine::InitializeResourceSubSystem() {
    std::string imageDirPath = "images/";
    ResourceManager::GetInstance().Initialize(imageDirPath);
}

void Engine::InitializeSceneManagerSubSystem() {
    SceneManager::GetInstance().Initialize(mRenderer, mScreenTexture);
}
