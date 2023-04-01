#ifndef GRAPHICS_ENGINE_RENDERER_HPP
#define GRAPHICS_ENGINE_RENDERER_HPP

#if defined(LINUX) || defined(MINGW)
#include <SDL2/SDL.h>
#else
#include <SDL.h>
#endif

/**
 * This class serves as an interface to
 * the main graphics renderer for our engine.
 */
class IGraphicsEngineRenderer {
   public:
    /**
     * Constructor
     */
    IGraphicsEngineRenderer(int w, int h) : mScreenWidth(w), mScreenHeight(h){};
    /**
     * Destructor
     */
    virtual ~IGraphicsEngineRenderer(){};
    /**
     * Set the color for the background whenever
     * the color is cleared.
     */
    virtual void SetRenderDrawColor(int r, int g, int b, int a) = 0;
    /**
     * Clear the screen
     */
    virtual void RenderClear() = 0;
    /**
     * Render whatever is in the backbuffer to
     * the screen.
     */
    virtual void RenderPresent() = 0;

   protected:
    int mScreenWidth{0};
    int mScreenHeight{0};
};

class SDLGraphicsEngineRenderer : public IGraphicsEngineRenderer {
   public:
    /**
     * Concrete implementation of constructor
     */
    SDLGraphicsEngineRenderer(int w, int h);
    /**
     * Destructor
     */
    ~SDLGraphicsEngineRenderer();

    void SetRenderDrawColor(int r, int g, int b, int a) override;
    /**
     * Clear the screen
     */
    void RenderClear() override;
    /**
     * Render whatever is in the backbuffer to
     * the screen.
     */
    void RenderPresent() override;
    /**
     * Get Pointer to Window
     */
    SDL_Window* GetWindow();
    /**
     * Get Pointer to Renderer
     */
    SDL_Renderer* GetRenderer();

   private:
    SDL_Window* mWindow = nullptr;
    SDL_Renderer* mRenderer = nullptr;
};

// #include <pybind11/pybind11.h>

// namespace py = pybind11;

// PYBIND11_MODULE(mygameengine, m){
//     m.doc() = "our game engine as a library"; // Optional docstring

//     py::class_<SDLGraphicsProgram>(m, "SDLGraphicsProgram")
//             .def(py::init<int,int>(), py::arg("w"), py::arg("h"))
//             .def("SetRenderDrawColor", &SDLGraphicsProgram::SetRenderDrawColor)
//             .def("RenderClear", &SDLGraphicsProgram::RenderClear)
//             .def("RenderPresent", &SDLGraphicsProgram::RenderPresent)
//             .def("GetWindow", &SDLGraphicsProgram::GetWindow)
//             .def("GetRenderer", &SDLGraphicsProgram::GetRenderer)
// }

#endif
