#include "inf_pch.hpp"
#include "influx/inf_hello-world.hpp"

namespace inf {
#if defined(NEO_PLATFORM_WINDOWS)
	HMODULE inf_vk = nullptr;
#elif defined(NEO_PLATFORM_LINUX)
	void* inf_vk = nullptr;
#endif

#if defined(NEO_PLATFORM_WINDOWS)
	HMODULE LoadLib(const char* name)
	{
		return LoadLibraryA(std::format("{}.dll", name).c_str());
	}
#elif defined(NEO_PLATFORM_LINUX)
	void* LoadLib(const char* name)
	{
		return dlopen(std::format("{}.so", name).c_str(), RTLD_LAZY);
	}
#endif

	template<typename FnType>
	FnType GetFn(const char* name, void* lib)
	{
	#if defined(NEO_PLATFORM_WINDOWS)
		return (FnType)GetProcAddress((HMODULE)lib, name);
	#elif defined(NEO_PLATFORM_LINUX)
		return (FnType)dlsym(lib, name);
	#endif
	}

	void init(void)
	{
		inf_vk = LoadLib("Influx-vk-bin");
		hello_world = GetFn<HelloWorld>("ivk_HelloWorld", inf_vk);
	}
}