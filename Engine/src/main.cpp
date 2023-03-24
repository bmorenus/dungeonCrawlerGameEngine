#include "Engine.hpp"
#include "IGraphicsEngineRenderer.hpp"

int main(int argc, char** argv){
	Engine engine;
	engine.InitializeGraphicsSubSystem();
	engine.InitializeResourceSubSystem();	 
    engine.Start();
	engine.MainGameLoop();
    engine.Shutdown();
	return 0;
}
