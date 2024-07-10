#if !defined(NEO_ENTITY_HPP)
#define NEO_ENTITY_HPP

#include "NeoInfused/neo_core.hpp"

namespace neo {
	class Entity {
	public:
		Entity(void) : m_Id(Entity::m_LastId++) {}
		~Entity(void) = default;
		static void Reset(void) { Entity::m_LastId = 0; }
		
		inline uint64_t id(void) const { return m_Id; }
	private:
		uint64_t m_Id;
		static uint64_t m_LastId;
	};
}

#endif // NEO_ENTITY_HPP