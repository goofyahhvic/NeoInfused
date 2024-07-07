#include "neo_pch.hpp"
#include "NeoInfused/game/neo_scene.hpp"

namespace neo {
    Scene* Scene::m_CurrentScene = nullptr;
    std::unordered_map<uint32_t, Scene*> Scene::m_Scenes;

    Scene::Scene(uint32_t id, Input* input)
    : m_Id(id), m_Input(input) {
        Scene::m_Scenes[id] = this;
    }
    Scene::~Scene(void) {
        Scene::m_Scenes.erase(m_Id);
    }

    void Scene::set_current(void* set_data, void* unset_data) {
        if (Scene::m_CurrentScene)
            Scene::m_CurrentScene->on_unset_current(unset_data);
        Scene::m_CurrentScene = this;
        this->on_set_current(set_data);
    }
} // namespace neo