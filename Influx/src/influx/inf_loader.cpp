#include "inf_pch.hpp"
#include "influx/inf_loader.hpp"

namespace inf {
	static void* currentLibrary = nullptr;

	static void loadLibrary(const char* lib_name)
	{
	#if defined(NEO_PLATFORM_WINDOWS)
		currentLibrary = LoadLibraryA(std::format("{}.dll", lib_name).c_str());
	#elif defined(NEO_PLATFORM_LINUX)
		currentLibrary = dlopen(std::format("{}/lib{}.so", std::filesystem::canonical("/proc/self/exe").parent_path().string(), lib_name).c_str(), RTLD_LAZY);
	#endif
	}

	template<typename FnT>
	static FnT getFn(const char* name)
	{
	#if defined(NEO_PLATFORM_WINDOWS)
		return (FnT)GetProcAddress((HMODULE)currentLibrary, name);
	#elif defined(NEO_PLATFORM_LINUX)
		return (FnT)dlsym(currentLibrary, name);
	#endif
	}

	void Loader::Load(RendererAPI api)
	{
		if (api == INF_API_VULKAN)
			loadLibrary("Influx-vk-bin");

		extension_count = getFn<ExtensionCount>("ExtensionCountE");
	}
	void Loader::Unload(void)
	{
		extension_count = nullptr;

	#if defined(NEO_PLATFORM_WINDOWS)
		FreeLibrary((HMODULE)currentLibrary);
	#elif defined(NEO_PLATFORM_LINUX)
		dlclose(currentLibrary);
	#endif
		currentLibrary = nullptr;
	}
}
