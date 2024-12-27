#if !defined(INF_WINDOW_SURFACE)
#define INF_WINDOW_SURFACE

#include "inf_loader.hpp"

namespace neo {
	namespace window { class window_t; }
	using window_t = window::window_t;
} // namespace neo

namespace inf {
	class window_surface_t {
	public:
		window_surface_t(neo::window_t* window);
		void destroy(void);
		inline ~window_surface_t(void) { this->destroy(); }

		window_surface_t(const window_surface_t&) = delete;
		window_surface_t& operator=(const window_surface_t&) = delete;

		[[nodiscard]] inline glm::uvec2 size(void) const { return *m_Size; }
		[[nodiscard]] inline uint32_t  width(void) const { return m_Size->x; }
		[[nodiscard]] inline uint32_t height(void) const { return m_Size->y; }

		inline operator bool(void) const { return m_Surface; }
		inline Loader::window_surface_t* native(void) { return m_Surface; }
	public:
		neo::window_t* window;
	private:
		Loader::window_surface_t* m_Surface;
		const glm::uvec2* m_Size;
	};
} // namespace inf

#endif // INF_WINDOW_SURFACE