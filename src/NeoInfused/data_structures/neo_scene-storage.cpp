#include "neo_pch.hpp"
#include "NeoInfused/data_structures/neo_scene-storage.hpp"

namespace neo {
	Scene& SceneStorage::_add_scene(std::unique_ptr<Scene>&& scene)
	{
		m_LastScene = scene->id();
		NEO_ASSERT(m_LastScene, "0 is not a valid scene id!");
		if (!m_CurrentScene)
			m_CurrentScene = m_LastScene;
		m_Scenes.emplace(m_LastScene, std::move(scene));
		return *m_Scenes.at(m_LastScene);
	}
	void SceneStorage::destroy_scene(uint32_t id)
	{
		if (m_CurrentScene == id)
			m_CurrentScene = 0;
		m_Scenes.erase(id);
	}
} // namespace neo
