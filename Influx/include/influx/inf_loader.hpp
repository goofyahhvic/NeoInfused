#if !defined(INF_LOADER_HPP)
#define INF_LOADER_HPP

enum inf_RendererAPI {
	INF_API_NONE = 0, INF_API_VULKAN
};

namespace inf {
	using RendererAPI = inf_RendererAPI;
	namespace Loader {
		void Load(RendererAPI api);
		void Unload(void);

		typedef uint32_t (*ExtensionCount)(void);
		inline ExtensionCount extension_count = nullptr;
	}
} // namespace inf

#endif // INF_LOADER_HPP