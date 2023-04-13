#include "Engine.hpp"

#include <filesystem>
#include <iterator>
#include <map>
#include <memory>
#include <string>
namespace fs = std::filesystem;

bool show_demo_window = false;
bool show_another_window = false;
ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

std::vector<SDL_Texture*> tmpp;
std::vector<int> tw, th;

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
        if (e.type == SDL_WINDOWEVENT &&
            e.window.event == SDL_WINDOWEVENT_CLOSE &&
            e.window.windowID == SDL_GetWindowID(mWindow)) {
            *quit = true;
        }

        SceneManager::GetInstance().AcceptInput(e, mScreenEditorPos);
    }
}

void Engine::Update() {
    SceneManager::GetInstance().Update();
}

void Engine::Render(ImGuiIO& mIo) {
    ImGui_ImplSDLRenderer_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    SDL_SetRenderTarget(mRenderer, mScreenTexture);
    SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, 0);
    SDL_RenderClear(mRenderer);
    SceneManager::GetInstance().Render();
    ImGui::NewFrame();

    ImGuiWindowFlags window_flags = 1 << 10;
    bool op = true;

    static int selected_level = -1;
    const char* names[] = {"Custom Level",
                           "Level 1: The Awakening"};
    static bool toggles[] = {true, false, false, false};
    {
        ImGui::Begin("Level Section Menu", &op, window_flags);
        ImGui::PushItemWidth(ImGui::GetFontSize() * -12);
        if (ImGui::TreeNode("Select your level:")) {
            static int selected = 0;
            for (int n = 0; n < 2; n++) {
                char buf[32];
                sprintf(buf, "%s", names[n]);
                if (ImGui::Selectable(buf, selected == n))
                    selected = n;
            }
            ImGui::TreePop();
        }
        ImGui::PopItemWidth();
        ImGui::End();
    }
    {
        ImGui::Begin("Dear ImGui Demo", &op, window_flags);
        ImGui::PushItemWidth(ImGui::GetFontSize() * -12);
        static int current_tile_index = 0;
        ImGui::SeparatorText("Game Object Selection:");
        for (int i = 0; i < SceneManager::GetInstance().GetCharacterCreators().size(); i++) {
            bool isClick = false;
            ImGui::PushID(i);
            ImVec2 size = ImVec2(32.0f, 32.0f);
            ImVec2 uv0 = ImVec2(0.0f, 0.0f);
            ImVec2 uv1 = ImVec2(32.0f / tw[i], 32.0f / th[i]);
            ImVec4 bg_col = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);
            ImVec4 tint_col = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
            if (ImGui::ImageButton("", tmpp[i], size, uv0, uv1, bg_col, tint_col)) {
                current_tile_index = i;
            }
            if (current_tile_index == i)
                ImGui::SetItemDefaultFocus();
            ImGui::PopID();
            ImGui::SameLine();
        }
        SceneManager::GetInstance().setCharacterCreator(SceneManager::GetInstance().GetCharacterCreators()[current_tile_index]);
        ImGui::NewLine();
        static int clicked = 0;
        ImGui::SeparatorText("Level Save");
        static char filename[64] = "";
        ImGui::InputText(".gamefile", filename, 64);
        ImGui::NewLine();
        if (ImGui::Button("Save Level")) {
            GameLevel* gameLevel = SceneManager::GetInstance().BuildGameLevel(filename);
            FileManager::GetInstance().SaveLevel(filename, gameLevel);
        }
        ImGui::SeparatorText("Level Load");
        if (ImGui::TreeNode("Select your level:")) {
            static int selected = 0;
            for (int n = 0; n < 2; n++) {
                char buf[32];
                sprintf(buf, "%s", names[n]);
                if (ImGui::Selectable(buf, selected == n))
                    selected = n;
            }
            ImGui::TreePop();
        }
        ImGui::PopItemWidth();
        ImGui::End();
    }
    {
        ImGui::Begin("Scene Editor", NULL, ImGuiWindowFlags_NoTitleBar);
        ImGui::Image(mScreenTexture, ImVec2(640, 360));
        mScreenEditorPos = ImGui::GetWindowPos();
        ImGui::End();
    }
    SDL_SetRenderTarget(mRenderer, NULL);

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
    // ImGui::StyleColorsDark();
    ImGui::StyleColorsLight();

    // Setup Platform/Renderer backends
    ImGui_ImplSDL2_InitForSDLRenderer(mWindow, mRenderer);
    ImGui_ImplSDLRenderer_Init(mRenderer);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
    while (!quit) {
        Input(&quit);
        SDL_Delay(80);  // Frame capping hack
        Update();
        Render(mIo);
    }
}

void Engine::Start() {
    if (mRenderer != nullptr) {
        std::cout << "Initializing Graphics Subsystem\n";
    } else {
        std::cout << "No Graphics Subsystem initialized\n";
    }

    tw.resize(SceneManager::GetInstance().GetCharacterCreators().size());
    th.resize(SceneManager::GetInstance().GetCharacterCreators().size());
    for (int i = 0; i < SceneManager::GetInstance().GetCharacterCreators().size(); i++) {
        auto t = SceneManager::GetInstance().CreateTexture(SceneManager::GetInstance().GetCharacterCreators()[i]->imageFilePath);
        tmpp.push_back(t);
        SDL_QueryTexture(tmpp[i], nullptr, nullptr, &tw[i], &th[i]);
    }
}

void Engine::Shutdown() {
    SceneManager::GetInstance().Shutdown();
    // ImGui Cleanup
    ImGui_ImplSDLRenderer_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();

    SDL_DestroyRenderer(mRenderer);
    SDL_DestroyWindow(mWindow);
    SDL_Quit();
}

int Engine::InitializeGraphicsSubSystem() {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER) != 0) {
        SDL_Log("Error: %s\n", SDL_GetError());
        return 0;
    }

    SDL_WindowFlags window_flags = (SDL_WindowFlags)(SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);
    mWindow = SDL_CreateWindow("Dear ImGui SDL2+SDL_Renderer example", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, window_flags);
    mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
    mScreenTexture = SDL_CreateTexture(mRenderer, SDL_PIXELFORMAT_ABGR8888, SDL_TEXTUREACCESS_TARGET, 640, 360);

    if (mRenderer == NULL) {
        SDL_Log("Error creating SDL_Renderer!");
        return 0;
    }
    std::cout << mRenderer << mRenderer;
    std::cout << "Graphics System Initialized" << std::endl;
    return 1;
}

void Engine::InitializeResourceSubSystem() {
    std::string imageDirPath = "images/";
    ResourceManager::GetInstance().Initialize(imageDirPath);
}

void Engine::InitializeSceneManagerSubSystem() {
    SceneManager::GetInstance().Initialize(mRenderer);
}

void Engine::InitializeFileManagerSubSystem() {
    FileManager::GetInstance().Initialize();
}