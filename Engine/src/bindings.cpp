#include <SDL_render.h>
#include "./../include/GameEntity.hpp"
#include "./../include/PlayerGameEntity.hpp"

#include <glad/glad.h>
#include "./../include/Scene.hpp"
#include "./../include/Application.hpp"
#include "./../include/Component.hpp"
#include "./../include/PlayerGameEntity.hpp"

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;

PYBIND11_MODULE(mygameengine, m) {
    py::class_<Application>(m, "Application")
        .def(py::init<>())
        .def("start_up", &Application::StartUp)
        .def("shut_down", &Application::ShutDown)
        .def("get_scene", &Application::GetScene)
        .def("get_input", &Application::GetInput)
        .def("poll", &Application::Poll)
        .def("loop", &Application::Loop);

    py::class_<Scene>(m, "Scene")
        .def(py::init<>())
        .def("create_new_game_entity", &Scene::CreateNewGameEntity)
        //.def("load_scene_from_file", &Scene::LoadSceneFromFile)
        .def("set_scene_status", &Scene::SetSceneStatus)
        .def("get_scene_status", &Scene::GetSceneStatus)
        .def("get_main_character", &Scene::GetMainCharacter);

    py::class_<GameEntity, std::shared_ptr<GameEntity>>(m, "GameEntity")
        .def(py::init<>())
        .def("get_transform", &GameEntity::GetTransform);

    py::class_<PlayerGameEntity, GameEntity, std::shared_ptr<PlayerGameEntity>>(m, "PlayerGameEntity")
        .def(py::init<>());

    py::class_<TransformComponent>(m, "TransformComponent")
        .def(py::init<>())
        .def("set_w", &TransformComponent::SetW)
        .def("set_h", &TransformComponent::SetH)
        .def("set_wh", &TransformComponent::SetWH)
        .def("set_x", &TransformComponent::SetX)
        .def("set_y", &TransformComponent::SetY)
        .def("set_xy", &TransformComponent::SetXY)
        .def("get_h", &TransformComponent::GetH)
        .def("get_w", &TransformComponent::GetW)
        .def("get_x", &TransformComponent::GetX)
        .def("get_y", &TransformComponent::GetY)
        .def("get_rectangle", &TransformComponent::GetRectangle);

    py::class_<InputComponent>(m, "InputComponent")
        .def(py::init<>());
}