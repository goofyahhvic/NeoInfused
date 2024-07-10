#include "neo_pch.hpp"
#include "NeoInfused/game/neo_component-registry.hpp"

namespace neo {
	ComponentRegistry* ComponentRegistry::m_This = nullptr;

	ComponentRegistry::ComponentRegistry(void) {
		NEO_ASSERT(!ComponentRegistry::m_This, "Cannot create multiple instances of ComponentRegistry!");
		ComponentRegistry::m_This = this;
	}
	ComponentRegistry::~ComponentRegistry(void) {

	}
}
