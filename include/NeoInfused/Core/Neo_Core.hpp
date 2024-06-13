#if !defined(NEO_CORE_HPP)
#define NEO_CORE_HPP

#include "NeoInfused/Core/Neo_Color.hpp"
#include "NeoInfused/Core/Neo_Time.hpp"
#include <cstdint>

#if defined(NEO_PLATFORM_LINUX)

	#ifdef NEO_BUILD_SHARED
		#define NEO_API __attribute__((visibility("default")))
	#else
		#define NEO_API 
	#endif

#elif defined(NEO_PLATFORM_WINDOWS)

    #ifdef NEO_BUILD_SHARED
		#define NEO_API __declspec(dllexport)
	#elif NEO_IMPORT_SHARED
		#define NEO_API __declspec(dllimport)
	#else // building or using static lib
		#define NEO_API 
	#endif
#else

    #error "Platform not supported. Did you forget to define NEO_PLATFORM_LINUX or NEO_PLATFORM_WINDOWS?"

#endif // NEO_PLATFORM_LINUX

#define NEO_FORMAT(...) std::format(__VA_ARGS__)

#if defined(NEO_PLATFORM_LINUX)
    #define C_STR c_str()
#elif defined(NEO_PLATFORM_WINDOWS)
    #define C_STR string().c_str()
#endif // NEO_PLATFORM_LINUX

#if !defined(NEO_CONFIG_DIST)

    #define NEO_ASSERT(x, ...) if(!(x)) {\
                                throw std::runtime_error(NEO_FORMAT(__VA_ARGS__));\
                               }
    
    #define NEO_ASSERT_FUNC(x, ...) NEO_ASSERT(x, __VA_ARGS__);

#else
    #define NEO_ASSERT(x, ...)
    #define NEO_ASSERT_FUNC(x, ...) x;

#endif // NEO_CONFIG_DIST

#if !defined(NEO_CONFIG_DIST)

    #define NEO_TRACE_LOG(...) std::cout << NEO_FORMAT(NEO_FONT_BOLD                "{0}[Neo]" NEO_COLOR_RSET " {1}\n", neo::core::Time::GetHoursMinutesSeconds(), NEO_FORMAT(__VA_ARGS__)) 
    #define NEO_INFO_LOG(...)  std::cout << NEO_FORMAT(NEO_FONT_BOLD NEO_COLOR_FGRN "{0}[Neo]" NEO_COLOR_RSET " {1}\n", neo::core::Time::GetHoursMinutesSeconds(), NEO_FORMAT(__VA_ARGS__)) 
    #define NEO_WARN_LOG(...)  std::cout << NEO_FORMAT(NEO_FONT_BOLD NEO_COLOR_FYEL "{0}[Neo]" NEO_COLOR_RSET " {1}\n", neo::core::Time::GetHoursMinutesSeconds(), NEO_FORMAT(__VA_ARGS__)) 
    #define NEO_ERROR_LOG(...) std::cout << NEO_FORMAT(NEO_FONT_BOLD NEO_COLOR_FRED "{0}[Neo]" NEO_COLOR_RSET " {1}\n", neo::core::Time::GetHoursMinutesSeconds(), NEO_FORMAT(__VA_ARGS__))
    #define NEO_FATAL_LOG(...) std::cout << NEO_FORMAT(NEO_FONT_BOLD NEO_COLOR_BRED "{0}[Neo]" NEO_COLOR_RSET " {1}\n", neo::core::Time::GetHoursMinutesSeconds(), NEO_FORMAT(__VA_ARGS__)) 

#else
    #define NEO_TRACE_LOG(...)
    #define NEO_INFO_LOG(...)
    #define NEO_WARN_LOG(...)
    #define NEO_ERROR_LOG(...)
    #define NEO_FATAL_LOG(...)

#endif // NEO_CONFIG_DIST

namespace neo {
#if defined(NEO_ID32)
    using id_t      = uint32_t;
    using index_t   = uint32_t;

    #define NEO_ID_MAX    UINT32_MAX;
    #define NEO_INDEX_MAX UINT32_MAX;
#elif defined(NEO_ID16)
    using id_t      = uint16_t;
    using index_t   = uint16_t;

    #define NEO_ID_MAX    UINT16_MAX;
    #define NEO_INDEX_MAX UINT16_MAX;
#elif defined(NEO_ID8)
    using id_t      = uint8_t;
    using index_t   = uint8_t;

    #define NEO_ID_MAX    UINT8_MAX;
    #define NEO_INDEX_MAX UINT8_MAX;
#else
    using id_t      = uint64_t;
    using index_t   = uint64_t;

    #define NEO_ID_MAX    UINT64_MAX;
    #define NEO_INDEX_MAX UINT64_MAX;
#endif
    using id8_t      = uint8_t;
    using id16_t     = uint16_t;
    using id32_t     = uint32_t;
    using id64_t     = uint64_t;

    using index8_t   = uint8_t;
    using index16_t  = uint16_t;
    using index32_t  = uint32_t;
    using index64_t  = uint64_t;

    struct InitInfo {
        int argc;
        char** argv;
        uint32_t TextureRegistrySize;
    };

    class Core {
        Core(void) = default;
        ~Core(void) = default;
    public:
        static void Init(const InitInfo& info);
        static void Terminate();

        static inline const std::string& GetExecPath(void) { return m_ExecPath; }
        static inline const std::string& GetExecDir(void) { return m_ExecDir; }

        static int    argc(void) { return m_Argc; }
        static char** argv(void) { return m_Argv; }
    private:
        static int m_Argc;
        static char** m_Argv;
        static std::string m_ExecPath, m_ExecDir;
    };
} // namespace neo

#endif // NEO_CORE_HPP