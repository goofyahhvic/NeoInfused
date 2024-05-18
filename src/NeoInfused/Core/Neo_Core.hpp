#if !defined(NEO_CORE_HPP)
#define NEO_CORE_HPP

#include "NeoInfused/Core/Neo_Color.hpp"
#include "NeoInfused/Core/Neo_Time.hpp"

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

#if defined(NEO_PLATFORM_LINUX)
    #define NEO_FORMAT(...) fmt::format(__VA_ARGS__)
#elif defined(NEO_PLATFORM_WINDOWS)
    #define NEO_FORMAT(...) std::format(__VA_ARGS__)
#endif

#if !defined(NEO_CONFIG_DIST)

    #define NEO_ASSERT(x, ...) if(!(x)) {\
                                throw std::runtime_error(NEO_FORMAT(__VA_ARGS__));\
                                return;\
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

#define NEO_SUCCESS 0
#define NEO_FAILURE -1

namespace neo_core {
#if defined(NEO_ID_4_BYTES)
    #define NEO_ID    uint32_t
    #define NEO_INDEX uint32_t
    using id_t      = uint32_t;
    using index_t   = uint32_t;
#elif defined(NEO_ID_2_BYTES)
    #define NEO_ID    uint16_t
    #define NEO_INDEX uint16_t
    using id_t      = uint16_t;
    using index_t   = uint16_t;
#elif defined(NEO_ID_1_BYTE)
    #define NEO_ID    uint8_t
    #define NEO_INDEX uint8_t
    using id_t      = uint8_t;
    using index_t   = uint8_t;
#else
    #define NEO_ID    uint64_t
    #define NEO_INDEX uint64_t
    using id_t      = uint64_t;
    using index_t   = uint64_t;
#endif // NEO_ID_16_BYTES

    using id8_t      = uint8_t;
    using id16_t     = uint16_t;
    using id32_t     = uint32_t;
    using id64_t     = uint64_t;

    using index8_t   = uint8_t;
    using index16_t  = uint16_t;
    using index32_t  = uint32_t;
    using index64_t  = uint64_t;

    using u8         = uint8_t;
    using u16        = uint16_t;
    using u32        = uint32_t;
    using u64        = uint64_t;

    using s8        = int8_t;
    using s16       = int16_t;
    using s32       = int32_t;
    using s64       = int64_t;

    using i8        = int8_t;
    using i16       = int16_t;
    using i32       = int32_t;
    using i64       = int64_t;

    using namespace neo;
    struct Size {
        size_t w, h;
    };
    struct String {
        String(void) : data(nullptr), size(1) {}
        String(char* data) : data(data), size(strlen(data)) {}
        String(char* data, size_t size) : data(data), size(size) {}
        ~String() = default;
        char* data;
        size_t size;
    };
    struct StringConst {
        StringConst(void) : data(nullptr), size(1) {}
        StringConst(const char* data) : data(data), size(strlen(data)) {}
        StringConst(const char* data, size_t size) : data(data), size(size) {}
        ~StringConst() = default;
        const char* data;
        size_t size;
    };
} // namespace neo_core

namespace neo {
    class Internal {
        Internal(void) = default;
        ~Internal(void) = default;
    public:
        static int32_t Init(int argc, char* argv[]);
        static void    Terminate();

        static inline const neo_core::StringConst& GetError(void) { return error; }

        static inline neo_core::String GetExecutablePath(void)   { return { exec_path.data(),   exec_folder.size() }; }
        static inline neo_core::String GetExecutableFolder(void) { return { exec_folder.data(), exec_folder.size() }; }

        static int    argc(void) { return _argc; }
        static char** argv(void) { return _argv; }

    private:
        static int _argc;
        static char** _argv;
        static neo_core::StringConst error;
        static std::string exec_path, exec_folder, exec_name;
    };
} // namespace neo

namespace neo_core {
    using namespace neo;
    inline int32_t init(int argc, char* argv[]) { return Internal::Init(argc, argv); }
    inline void    terminate(void)              { return Internal::Terminate(); }

    inline const char* get_error(void)        { return Internal::GetError().data; }
    inline StringConst get_error(void*)       { return Internal::GetError(); }

    inline const char* get_exec_path(void)    { return Internal::GetExecutablePath().data; }
    inline String      get_exec_path(void*)   { return Internal::GetExecutablePath(); }

    inline const char* get_exec_folder(void)  { return Internal::GetExecutableFolder().data; }
    inline String      get_exec_folder(void*) { return Internal::GetExecutableFolder(); }
} // namespace neo_core

namespace neo {
#if defined(NEO_ID32)
    #define NEO_ID    uint32_t
    #define NEO_INDEX uint32_t
    using id_t      = uint32_t;
    using index_t   = uint32_t;

    #define NEO_ID_MAX    UINT32_MAX;
    #define NEO_INDEX_MAX UINT32_MAX;
#elif defined(NEO_ID16)
    #define NEO_ID    uint16_t
    #define NEO_INDEX uint16_t
    using id_t      = uint16_t;
    using index_t   = uint16_t;

    #define NEO_ID_MAX    UINT16_MAX;
    #define NEO_INDEX_MAX UINT16_MAX;
#elif defined(NEO_ID8)
    #define NEO_ID    uint8_t
    #define NEO_INDEX uint8_t
    using id_t      = uint8_t;
    using index_t   = uint8_t;

    #define NEO_ID_MAX    UINT8_MAX;
    #define NEO_INDEX_MAX UINT8_MAX;
#else
    #define NEO_ID    uint64_t
    #define NEO_INDEX uint64_t
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

    using u8         = uint8_t;
    using u16        = uint16_t;
    using u32        = uint32_t;
    using u64        = uint64_t;

    using s8        = int8_t;
    using s16       = int16_t;
    using s32       = int32_t;
    using s64       = int64_t;

    using i8        = int8_t;
    using i16       = int16_t;
    using i32       = int32_t;
    using i64       = int64_t;
} // namespace neo

#endif // NEO_CORE_HPP