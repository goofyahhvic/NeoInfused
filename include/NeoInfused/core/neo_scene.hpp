#if !defined(NEO_SCENE_HPP)
#define NEO_SCENE_HPP

#include "NeoInfused/core/neo_input.hpp"

namespace neo {
	class Scene {
	public:
		Scene(uint32_t id) : m_Id(id) {}
		virtual ~Scene(void) = default;
	public:
		virtual void on_set_current(void) {}
		virtual void on_unset_current(void) {}

		[[nodiscard]] inline uint32_t id(void) const { return m_Id; }
	protected:
		const uint32_t m_Id;
	};
} // namespace neo

#endif // NEO_SCENE_HPP