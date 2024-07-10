#if !defined (NEO_COMPONENT_REGISTRY_HPP)
#define NEO_COMPONENT_REGISTRY_HPP

#include "neo_entity.hpp"

namespace neo {
	class ComponentRegistry {
	public:
		ComponentRegistry(void);
		~ComponentRegistry(void);

		static ComponentRegistry* Get(void) { return ComponentRegistry::m_This; }
	private:
		static ComponentRegistry* m_This;
	};
	using ComponentReg = ComponentRegistry;
}

#endif // NEO_COMPONENT_REGISTRY_HPP