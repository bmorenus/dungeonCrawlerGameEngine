#include "IGraphicsEngineRenderer.hpp"

#include <stdlib.h>
#include <time.h>

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
///////////////////////////////////////////////////////////////////
/// (Other Render implementations here (e.g. Direct3D)
///////////////////////////////////////////////////////////////////

// ...

///////////////////////////////////////////////////////////////////
/// SDLGraphicsEngineRenderer Implementation
//////////////////////////////////////////////////////////////////
SDLGraphicsEngineRenderer::SDLGraphicsEngineRenderer(int w, int h) : IGraphicsEngineRenderer(w, h) {
    srand(time(nullptr));

    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        std::cerr << "SDL could not initialize! SDL Error: " << SDL_GetError() << "\n";
        exit(1);
    }

    mWindow = SDL_CreateWindow("Lab", 100, 100, mScreenWidth, mScreenHeight, SDL_WINDOW_SHOWN);

    if (nullptr == mWindow) {
        std::cerr << "Window could not be created! SDL Error: " << SDL_GetError() << "\n";
        exit(1);
    }

    mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED);
    if (nullptr == mRenderer) {
        std::cerr << "Renderer could not be created! SDL Error: " << SDL_GetError() << "\n";
        exit(1);
    }

    std::cout << "No SDL errors Detected in during init\n\n";
}

SDLGraphicsEngineRenderer::~SDLGraphicsEngineRenderer() {
    SDL_DestroyRenderer(mRenderer);
    SDL_DestroyWindow(mWindow);

    mRenderer = nullptr;
    mWindow = nullptr;

    SDL_Quit();
}

void SDLGraphicsEngineRenderer::SetRenderDrawColor(int r, int g, int b, int a) {
    SDL_SetRenderDrawColor(mRenderer, r, g, b, a);
}

void SDLGraphicsEngineRenderer::RenderClear() {
    SDL_RenderClear(mRenderer);
}

void SDLGraphicsEngineRenderer::RenderPresent() {
    SDL_RenderPresent(mRenderer);
}

// Get Pointer to Window
SDL_Window* SDLGraphicsEngineRenderer::GetWindow() {
    return mWindow;
}

// Get Pointer to Renderer
SDL_Renderer* SDLGraphicsEngineRenderer::GetRenderer() {
    return mRenderer;
}
