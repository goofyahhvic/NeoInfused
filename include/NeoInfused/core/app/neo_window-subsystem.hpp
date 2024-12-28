#if !defined(NEO_WINDOW_SYSTEM_SET_HPP)
#define NEO_WINDOW_SYSTEM_SET_HPP

#include "../neo_window.hpp"
#include "../neo_input.hpp"

namespace neo {
	namespace subsystems {
		class window_t {
		public:
			window_t(uint32_t width = 1280,
					 uint32_t height = 720,
					 const char* title = "Unnamed Window");
			inline ~window_t(void) { s_This = nullptr; }

			static void AddSystems(void);

			static void OnEvent(neo::event_t& e);
		public:
			window::window_t window;
			input_t input;
		private:
			static inline window_t* s_This = nullptr;
		};
	} // namespace subsystems
	using window_subsystem_t = subsystems::window_t;
} // namespace neo

#endif // NEO_WINDOW_SYSTEM_SET_HPP