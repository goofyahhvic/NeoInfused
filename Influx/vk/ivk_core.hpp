#if !defined(IVK_CORE_HPP)
#define IVK_CORE_HPP

#if defined(NEO_PLATFORM_WINDOWS)

	#define IVK_API extern "C" __declspec(dllexport)

#elif defined(NEO_PLATFORM_LINUX)

	#define IVK_API extern "C" __attribute__((visibility("default")))

#endif

#if !defined(NEO_CONFIG_DIST)

#define IVK_TRACE_LOG(...) std::clog << NEO_FORMAT(NEO_FONT_BOLD                "[{0}][InfVk]" NEO_COLOR_RSET " {1}\n", std::format("{:%X}", std::chrono::zoned_time(std::chrono::current_zone(), std::chrono::system_clock::now())), NEO_FORMAT(__VA_ARGS__)) 
#define IVK_INFO_LOG(...)  std::clog << NEO_FORMAT(NEO_FONT_BOLD NEO_COLOR_FGRN "[{0}][InfVk]" NEO_COLOR_RSET " {1}\n", std::format("{:%X}", std::chrono::zoned_time(std::chrono::current_zone(), std::chrono::system_clock::now())), NEO_FORMAT(__VA_ARGS__)) 
#define IVK_WARN_LOG(...)  std::clog << NEO_FORMAT(NEO_FONT_BOLD NEO_COLOR_FYEL "[{0}][InfVk]" NEO_COLOR_RSET " {1}\n", std::format("{:%X}", std::chrono::zoned_time(std::chrono::current_zone(), std::chrono::system_clock::now())), NEO_FORMAT(__VA_ARGS__)) 
#define IVK_ERROR_LOG(...) std::clog << NEO_FORMAT(NEO_FONT_BOLD NEO_COLOR_FRED "[{0}][InfVk]" NEO_COLOR_RSET " {1}\n", std::format("{:%X}", std::chrono::zoned_time(std::chrono::current_zone(), std::chrono::system_clock::now())), NEO_FORMAT(__VA_ARGS__))
#define IVK_FATAL_LOG(...) std::clog << NEO_FORMAT(NEO_FONT_BOLD NEO_COLOR_BRED "[{0}][InfVk]" NEO_COLOR_RSET " {1}\n", std::format("{:%X}", std::chrono::zoned_time(std::chrono::current_zone(), std::chrono::system_clock::now())), NEO_FORMAT(__VA_ARGS__))

#else
#define IVK_TRACE_LOG(...)
#define IVK_INFO_LOG(...)
#define IVK_WARN_LOG(...)
#define IVK_ERROR_LOG(...)
#define IVK_FATAL_LOG(...)

#endif // NEO_CONFIG_DIST
#define IVK_LOG_CONTINUE "\n\t\t"

#endif // IVK_CORE_HPP