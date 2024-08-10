#if !defined(NEO_RENDERER_HPP)
#define NEO_RENDERER_HPP

#include "NeoInfused/core/neo_window.hpp"

enum neo_RendererAPI {
	NEO_RENDERERAPI_NONE = 0,
	NEO_RENDERERAPI_OPENGL,
	NEO_RENDERERAPI_VULKAN
#if defined(NEO_PLATFORM_WINDOWS)
	, NEO_RENDERAPI_DIRECTX
#endif // NEO_PLATFORM_WINDOWS
};

namespace neo {
	using RendererAPI = neo_RendererAPI;
	class Context {
		friend class Core;
	public:
		static Context* Create_GL(void);
		static inline void Destroy(void) { if (s_Initialized) s_This->terminate(); delete s_This; s_This = nullptr; }

		[[nodiscard]] static inline Context& Get(void) { return *s_This; }
		[[nodiscard]] static inline RendererAPI API(void) { return (RendererAPI)s_API; }
		[[nodiscard]] static inline bool Initialized(void) { return s_Initialized; }
	public:
		virtual void initialize(Window* window) = 0;
		virtual void terminate(void) { s_Initialized = false; s_API = NEO_RENDERERAPI_NONE; }

		virtual void set_viewport(Window* window, uint32_t width, uint32_t height) = 0;
		virtual void new_frame(Window* window, const glm::vec4& color = { 0, 0, 0, 255 }) = 0;
		virtual void present(Window* window) = 0;
	protected:
		virtual inline ~Context(void) = default;
	protected:
		static inline Context* s_This = nullptr;
		static inline RendererAPI s_API = NEO_RENDERERAPI_NONE;
		static inline bool s_Initialized = false;
	};
}

#endif // NEO_RENDERER_HPP