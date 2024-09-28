#if !defined(INF_WINDOW_SURFACE)
#define INF_WINDOW_SURFACE

#include "inf_loader.hpp"

struct GLFWwindow;

namespace inf {
	class WindowSurface {
	public:
		WindowSurface(GLFWwindow* window);
		void destroy(void);
		inline ~WindowSurface(void) { if (m_Surface) this->destroy(); }

		WindowSurface(const WindowSurface&) = delete;
		WindowSurface& operator=(const WindowSurface&) = delete;

		inline operator bool(void) const { return m_Surface; }
	private:
		Loader::WindowSurface* m_Surface;
	};
} // namespace inf

#endif // INF_WINDOW_SURFACE