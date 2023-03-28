#include "Engine.hpp"
#include "IGraphicsEngineRenderer.hpp"

#if !SDL_VERSION_ATLEAST(2, 0, 17)
#error This backend requires SDL 2.0.17+ because of SDL_RenderGeometry() function
#endif

int main(int argc, char** argv) {
    Engine engine;
    engine.InitializeGraphicsSubSystem();
    engine.InitializeResourceSubSystem();
    engine.InitializeSceneManagerSubSystem();
    engine.Start();
    engine.MainGameLoop();
    engine.Shutdown();
    return 0;
}
