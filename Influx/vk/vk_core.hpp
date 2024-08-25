#if !defined(VK_CORE_HPP)
#define VK_CORE_HPP

#include "NeoInfused/neo_core.hpp"

#if defined(NEO_PLATFORM_WINDOWS)

	#define EXPORT_FN extern "C" __declspec(dllexport)

#elif defined(NEO_PLATFORM_LINUX)

	#define EXPORT_FN extern "C" __attribute__((visibility("default")))

#endif

#if !defined(NEO_CONFIG_DIST)

#define VK_TRACE_LOG(...) std::clog << NEO_FORMAT(NEO_FONT_BOLD                "[{0}][Vulkan]" NEO_COLOR_RSET " {1}\n", std::format("{:%X}", std::chrono::zoned_time(std::chrono::current_zone(), std::chrono::system_clock::now())), NEO_FORMAT(__VA_ARGS__)) 
#define VK_INFO_LOG(...)  std::clog << NEO_FORMAT(NEO_FONT_BOLD NEO_COLOR_FGRN "[{0}][Vulkan]" NEO_COLOR_RSET " {1}\n", std::format("{:%X}", std::chrono::zoned_time(std::chrono::current_zone(), std::chrono::system_clock::now())), NEO_FORMAT(__VA_ARGS__)) 
#define VK_WARN_LOG(...)  std::clog << NEO_FORMAT(NEO_FONT_BOLD NEO_COLOR_FYEL "[{0}][Vulkan]" NEO_COLOR_RSET " {1}\n", std::format("{:%X}", std::chrono::zoned_time(std::chrono::current_zone(), std::chrono::system_clock::now())), NEO_FORMAT(__VA_ARGS__)) 
#define VK_ERROR_LOG(...) std::clog << NEO_FORMAT(NEO_FONT_BOLD NEO_COLOR_FRED "[{0}][Vulkan]" NEO_COLOR_RSET " {1}\n", std::format("{:%X}", std::chrono::zoned_time(std::chrono::current_zone(), std::chrono::system_clock::now())), NEO_FORMAT(__VA_ARGS__))
#define VK_FATAL_LOG(...) std::clog << NEO_FORMAT(NEO_FONT_BOLD NEO_COLOR_BRED "[{0}][Vulkan]" NEO_COLOR_RSET " {1}\n", std::format("{:%X}", std::chrono::zoned_time(std::chrono::current_zone(), std::chrono::system_clock::now())), NEO_FORMAT(__VA_ARGS__))

#else
#define VK_TRACE_LOG(...)
#define VK_INFO_LOG(...)
#define VK_WARN_LOG(...)
#define VK_ERROR_LOG(...)
#define VK_FATAL_LOG(...)

#endif // NEO_CONFIG_DIST
#define VK_LOG_CONTINUE "\n\t\t"

#endif // VK_CORE_HPP