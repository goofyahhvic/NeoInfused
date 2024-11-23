#include "neo_pch.hpp"
#include "NeoInfused/core/neo_dynamic-library.hpp"

namespace neo {
	void dll_t::load(const wchar_t* wname)
	{
		if (!wname)
			return;

		if (m_Handle)
			this->unload();

		const wchar_t* end = wname;
		while (*++end);
		m_Name = std::string(wname, end);

		NEO_TRACE_LOG("Loading library {}", m_Name);
	#if defined(NEO_PLATFORM_WINDOWS)
		m_Handle = LoadLibraryW(NEO_FORMAT(L"{}.dll", wname).c_str());
	#elif defined(NEO_PLATFORM_LINUX)
		m_Handle = dlopen(NEO_FORMAT("{}/lib{}.so", std::filesystem::canonical("/proc/self/exe").parent_path().string(), m_Name).c_str(), RTLD_LAZY);
	#endif

		if (!m_Handle)
			throw std::runtime_error(NEO_FORMAT("Failed to load library {}!", m_Name));
	}

	void dll_t::load(const char* name)
	{
		if (!name)
			return;

		if (m_Handle)
			this->unload();

		m_Name = name;

		NEO_TRACE_LOG("Loading library {}", name);
	#if defined(NEO_PLATFORM_WINDOWS)
		m_Handle = LoadLibraryA(NEO_FORMAT("{}.dll", name).c_str());
	#elif defined(NEO_PLATFORM_LINUX)
		m_Handle = dlopen(NEO_FORMAT("{}/lib{}.so", std::filesystem::canonical("/proc/self/exe").parent_path().string(), name).c_str(), RTLD_LAZY);
	#endif

		if (!m_Handle)
			throw std::runtime_error(NEO_FORMAT("Failed to load library {}!", name));
	}

	void dll_t::unload(void)
	{
		if (!m_Handle)
			return;

		NEO_TRACE_LOG("Unloading library {}", m_Name);
	#if defined(NEO_PLATFORM_WINDOWS)
		FreeLibrary((HMODULE)m_Handle);
	#elif defined(NEO_PLATFORM_LINUX)
		dlclose(m_Handle);
	#endif
		m_Handle = nullptr;
		m_Name = std::string();
	}

	void* dll_t::fn(const char* name) const
	{
		if (!m_Handle)
			return nullptr;

		#if defined(NEO_PLATFORM_WINDOWS)
		return GetProcAddress((HMODULE)m_Handle, name);
		#elif defined(NEO_PLATFORM_LINUX)
		return dlsym(m_Handle, name);
		#endif
		return nullptr;
	}
} // namespace neo
