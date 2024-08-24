#if !defined(INF_LOADER_HPP)
#define INF_LOADER_HPP

namespace inf {
	enum class RendererAPI {
		None = 0, Vulkan = 1
	};

	namespace Loader {
		void Load(RendererAPI api);
		void Unload(void);

		typedef void (*HelloWorld)(void);
		inline HelloWorld hello_world = nullptr;
	}
} // namespace inf

#endif // INF_LOADER_HPP