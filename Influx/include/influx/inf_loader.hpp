#if !defined(INF_LOADER_HPP)
#define INF_LOADER_HPP

#include "inf_core.hpp"

#define INF_API_NONE 0
#define INF_API_VULKAN 1

namespace inf {
	using RendererAPI = unsigned char;
	// class that *loads* a rendering api library
	class Loader {
	public:
		inline Loader(RendererAPI api) { Loader::Load(api); }
		inline ~Loader(void) { Loader::Load(INF_API_NONE); }

		static void Load(RendererAPI api);
		static inline void Unload(void) { Loader::Load(INF_API_NONE); };

		static inline RendererAPI GetRendererAPI(void) { return s_RendererAPI; }
	public: // loaded functions
		typedef void (*InitAPIFn)(void);
		static inline InitAPIFn init_api = nullptr;

		typedef void (*ShutdownAPIFn)(void);
		static inline ShutdownAPIFn shutdown_api = nullptr;

		struct WindowSurface;

		typedef WindowSurface* (*CreateWindowSurfaceFN)(GLFWwindow*);
		static inline CreateWindowSurfaceFN create_window_surface = nullptr;

		typedef void (*DestroyWindowSurfaceFN)(WindowSurface*);
		static inline DestroyWindowSurfaceFN destroy_window_surface = nullptr;
	private:
		static inline RendererAPI s_RendererAPI = INF_API_NONE;
		static inline void* s_CurrentLibrary = nullptr;
	};

	inline bool g_Initialized = false;
	inline void InitializeAPI(void) { Loader::init_api(); g_Initialized = true; }
	inline void ShutdownAPI(void) { g_Initialized = false; Loader::shutdown_api(); }
} // namespace inf

#endif // INF_LOADER_HPP