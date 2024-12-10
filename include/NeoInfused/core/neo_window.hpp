#if !defined(NEO_WINDOW_HPP)
#define NEO_WINDOW_HPP

#include "neo_event.hpp"
#include "influx/inf_window-surface.hpp"
#include "../template/neo_double-list.hpp"

struct GLFWwindow;
namespace neo {
	namespace window {
		class window_t {
		public:
			window_t(uint32_t width, uint32_t height, const char* title);
			void destroy(void);
			inline ~window_t(void) { this->destroy(); }

			window_t(const window_t&) = delete;
			window_t& operator=(const window_t&) = delete;

			void focus(void);
			[[nodiscard]] inline bool focused(void) const { return m_Focus; }

			[[nodiscard]] inline uint32_t width(void) const { return m_Width; }
			[[nodiscard]] inline uint32_t height(void) const { return m_Height; }
			void set_size(uint32_t width, uint32_t height);

			void set_title(const char* title);
			[[nodiscard]] const char* title(void) const;

			[[nodiscard]] inline GLFWwindow* native(void) { return m_Window; }
			inline operator bool(void) const { return m_Window; }

			static void _SetGLFWCallbacks(GLFWwindow* _window);
		private:
			GLFWwindow* m_Window;
			uint32_t m_Width, m_Height;
			bool m_Focus = true;
		};
		using storage_t = double_list_t<window_t>;
	} // namespace window
	using window_t = window::window_t;
} // namespace neo

#endif // NEO_WINDOW_HPP