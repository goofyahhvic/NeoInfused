#if !defined(NEO_CORE_SUBSYSTEM_HPP)
#define NEO_CORE_SUBSYSTEM_HPP

#include "../neo_window.hpp"
#include "../neo_input.hpp"

namespace neo {
	namespace subsystems {
		class core_t {
		public:
			inline core_t(void) { InitCore(); }
			inline ~core_t(void) { ShutdownCore(); }
			inline void AddSystems(void) {}
		};
	} // namespace subsystems
	using core_subsystem_t = subsystems::core_t;
} // namespace neo

#endif // NEO_CORE_SUBSYSTEM_HPP