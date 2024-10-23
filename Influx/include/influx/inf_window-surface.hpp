#if !defined(INF_WINDOW_SURFACE)
#define INF_WINDOW_SURFACE

#include "inf_loader.hpp"

struct GLFWwindow;

namespace inf {
	class window_surface_t {
	public:
		window_surface_t(GLFWwindow* window);
		void destroy(void);
		inline ~window_surface_t(void) { if (m_Surface) this->destroy(); }

		window_surface_t(const window_surface_t&) = delete;
		window_surface_t& operator=(const window_surface_t&) = delete;

		inline operator bool(void) const { return m_Surface; }
	private:
		Loader::window_surface_t* m_Surface;
	};
} // namespace inf

#endif // INF_WINDOW_SURFACE