#include "Engine.hpp"
#include "Renderer.hpp"
#include <pybind11/pybind11.h>

namespace py = pybind11;

PYBIND11_MODULE(mygameengine, m) {

    py::class_<Engine>(m, "Engine")
        .def(py::init<>())
        .def("Start", &Engine::Start)
        .def("Shutdown", &Engine::Shutdown)
        .def("InitializeGraphicsSubSystem", &Engine::InitializeGraphicsSubSystem)
        .def("InitializeResourceSubSystem", &Engine::InitializeResourceSubSystem)
        .def("InitializeSceneManagerSubSystem", &Engine::InitializeSceneManagerSubSystem)
        .def("MainGameLoop", &Engine::MainGameLoop);

    py::class_<SceneManager>(m, "SceneManager")
        .def("add_test_game_objects", &SceneManager::AddTestGameObjects)
        .def("add_game_object", &SceneManager::AddGameObject)
        .def("create_game_object", &SceneManager::CreateGameObject)
        .def_static("get_instance", &SceneManager::GetInstance, py::return_value_policy::reference);
}
