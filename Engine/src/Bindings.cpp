#include <pybind11/pybind11.h>

#include "Engine.hpp"

namespace py = pybind11;

PYBIND11_MODULE(mygameengine, m) {
    /**
     * Engine class bindings
     **/
    py::class_<Engine>(m, "Engine")
        .def(py::init<>())
        .def("start", &Engine::Start, "Starts the engine.")
        .def("shutdown", &Engine::Shutdown, "Shuts down the engine.")
        .def("initialize_graphics_subsystem", &Engine::InitializeGraphicsSubSystem, "Initializes the graphics subsystem.")
        .def("initialize_resource_subsystem", &Engine::InitializeResourceSubSystem, "Initializes the resource subsystem.")
        .def("initialize_scene_manager_subsystem", &Engine::InitializeSceneManagerSubSystem, "Initializes the scene manager subsystem.")
        .def("main_game_loop", &Engine::MainGameLoop, "Runs the main game loop.");

    /**
     * SceneManager class bindings
     **/
    py::class_<SceneManager>(m, "SceneManager")
        .def("create_component", &SceneManager::CreateComponentWrapper, "Creates a component with the given key name and type.")
        .def("create_game_object", &SceneManager::CreateGameObjectWrapper, "Creates a game object with the given key name and object type.")
        .def("add_component", &SceneManager::AddComponentWrapper, "Adds a component to the game object with the given key name.")
        .def("add_game_object", &SceneManager::AddGameObjectWrapper, "Adds a game object to the scene manager.")
        .def("add_collision_object", &SceneManager::AddCollisionObjectWrapper, "Adds a collision object to the physics manager.")
        .def_static("get_instance", &SceneManager::GetInstance, py::return_value_policy::reference, "Returns the instance of the scene manager.");
}
