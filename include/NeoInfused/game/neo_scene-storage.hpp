#if !defined(NEO_SCENE_STORAGE_HPP)
#define NEO_SCENE_STORAGE_HPP

#include "neo_scene.hpp"

namespace neo {
	class SceneStorage {
	public:
		SceneStorage(void) = default;
		~SceneStorage(void) = default;

		template<typename T, typename... _Args>
		inline T& create_scene(_Args&&... __args) { return (T&)this->_add_scene(std::make_unique<T>(std::forward<_Args>(__args)...)); }
		void destroy_scene(uint32_t id);

		inline void clear(void) { m_Scenes.clear(); m_CurrentScene = 0; }
		[[nodiscard]] inline bool empty(void) { return m_Scenes.empty(); }

		[[nodiscard]] inline Scene& at(uint32_t id) { return *m_Scenes.at(id); }
		[[nodiscard]] inline const Scene& at(uint32_t id) const { return *m_Scenes.at(id); }

		[[nodiscard]] inline Scene& current(void) { return *m_Scenes.at(m_CurrentScene); }
		[[nodiscard]] inline const Scene& current(void) const { return *m_Scenes.at(m_CurrentScene); }
	private:
		Scene& _add_scene(std::unique_ptr<Scene>&& scene);
	private:
		uint32_t m_CurrentScene = 0, m_LastScene = 0;
		std::unordered_map<uint32_t, std::unique_ptr<Scene>> m_Scenes;
	};
}

#endif // NEO_SCENE_STORAGE_HPP