#include "inf_pch.hpp"
#include "influx/inf_loader.hpp"

namespace inf {
	static void* currentLibrary = nullptr;

	static void loadLibrary(const char* dll, const char* so)
	{
	#if defined(NEO_PLATFORM_WINDOWS)
		currentLibrary = LoadLibraryA(dll);
	#elif defined(NEO_PLATFORM_LINUX)
		currentLibrary = dlopen(so, RTLD_LAZY);
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
		if (api == RendererAPI::Vulkan)
			loadLibrary("Influx-vk-bin.dll", "libInflux-vk-bin.so");

		hello_world = getFn<HelloWorld>("HelloWorldE");
	}
	void Loader::Unload(void)
	{
		hello_world = nullptr;

	#if defined(NEO_PLATFORM_WINDOWS)
		FreeLibrary((HMODULE)currentLibrary);
	#elif defined(NEO_PLATFORM_LINUX)
		dlclose(currentLibrary);
	#endif
		currentLibrary = nullptr;
	}
}
