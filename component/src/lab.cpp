// Support Code written by Michael D. Shah
// Last Updated: 2/19/21
// Please do not redistribute without asking permission.


#include "Engine.hpp" // The main engine
#include "IGraphicsEngineRenderer.hpp" // The renderering engine

int main(int argc, char** argv){
	// Create an instance of an object for our engine
	Engine engine;
	// Initialize the Engine Subsystems
	engine.InitializeGraphicsSubSystem();	 
    // Once all subsystems have been initialized
    // Start the engine
    engine.Start();
    // Run our program forever
	engine.MainGameLoop();
    // Explicitly call Shutdown to terminate our engine
    engine.Shutdown();
	// When our program ends, it will exit scope,
    // the destructor will then be called
    // and clean up the program.
	return 0;
}
