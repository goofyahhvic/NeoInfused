#if !defined(INF_LOADER_HPP)
#define INF_LOADER_HPP

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

		typedef uint32_t (*ExtensionCountFn)(void);
		static inline ExtensionCountFn extension_count = nullptr;
	private:
		static inline RendererAPI s_RendererAPI = INF_API_NONE;
	};
} // namespace inf

#endif // INF_LOADER_HPP