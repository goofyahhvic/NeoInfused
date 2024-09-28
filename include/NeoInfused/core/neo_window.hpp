#if !defined(NEO_WINDOW_HPP)
#define NEO_WINDOW_HPP

#include "neo_event.hpp"
#include "influx/inf_window-surface.hpp"

struct GLFWwindow;
namespace neo {
	namespace gl { class Context; }

	class Window {
	public:
		[[nodiscard]] inline uint64_t id(void) const { return m_Id; }

		void focus(void);
		[[nodiscard]] inline bool focused(void) const { return m_Focus; }

		[[nodiscard]] inline uint32_t width(void) const { return m_Width; }
		[[nodiscard]] inline uint32_t height(void) const { return m_Height; }
		void set_size(uint32_t width, uint32_t height);

		void set_title(const char* title);
		[[nodiscard]] const char* title(void) const;

		inline operator bool(void) const { return m_Window; }
	public:
		bool should_close = false;
	private:
		friend class gl::Context;
		friend class Context;
		friend class WindowStorage;

		Window(void) = default;
		Window(uint32_t id, uint32_t width, uint32_t height, const char* title);
		void destroy(void);
		inline ~Window(void) { if (m_Window) this->destroy(); }

		Window(const Window&) = delete;
		Window& operator=(const Window&) = delete;

		static void _SetGLFWCallbacks(GLFWwindow* _window);
	public:
		static void _GLFWPollEvents(void);
	private:
		GLFWwindow* m_Window;
		inf::WindowSurface m_Surface;
		uint32_t m_Width, m_Height;
		uint32_t m_Id;
		bool m_Focus;
	};
} // namespace neo

#endif // NEO_WINDOW_HPP