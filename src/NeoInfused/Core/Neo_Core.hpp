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

namespace neo {
    #if !defined(NEO_APP)
    #define NEO_APP
    class App;
    #endif // NEO_APP
    
    namespace core {
        struct Size {
            size_t w, h;
        };
    } // namespace core

} // namespace neo

#define NEO_SUCCESS 0
#define NEO_FAILURE -1

namespace neo {
    namespace core {
        struct String {
            String(void) : data(""), size(1) {}
            String(char* data) : data(data), size(strlen(data)) {}
            String(char* data, size_t size) : data(data), size(size) {}
            ~String() = default;

            char* data;
            size_t size;
        };
        struct StringConst {
            StringConst(void) : data(""), size(1) {}
            StringConst(const char* data) : data(data), size(strlen(data)) {}
            StringConst(const char* data, size_t size) : data(data), size(size) {}
            ~StringConst() = default;

            const char* data;
            size_t size;
        };

    } // namespace core

    class Internal {
        Internal(void) = default;
        ~Internal(void) = default;
    public:
        static int32_t Init(int argc, char* argv[]);
        static void    Terminate();

        static inline const core::String& GetError(void) { return error; }

        static inline core::String GetExecutablePath(void)   { return { exec_path.data(),   exec_folder.size() }; }
        static inline core::String GetExecutableFolder(void) { return { exec_folder.data(), exec_folder.size() }; }

        static int argc(void) { return _argc; }
        static char** argv(void) { return _argv; }

    private:
        static int _argc;
        static char** _argv;
        static core::String error;
#if defined(NEO_PLATFORM_LINUX)
        static std::string exec_path, exec_folder, exec_name;
#elif defined(NEO_PLATFORM_WINDOWS)
        
#endif // NEO_PLATFORM_LINUX

    };

    namespace core {
        inline int32_t init(int argc, char* argv[]) { return Internal::Init(argc, argv); }
        inline void    terminate(void)              { return Internal::Terminate(); }

        inline const char* get_error(void)        { return Internal::GetError().data; }
        inline String      get_error(void*)       { return Internal::GetError(); }

        inline const char* get_exec_path(void)    { return Internal::GetExecutablePath().data; }
        inline String      get_exec_path(void*)   { return Internal::GetExecutablePath(); }

        inline const char* get_exec_folder(void)  { return Internal::GetExecutableFolder().data; }
        inline String      get_exec_folder(void*) { return Internal::GetExecutableFolder(); }

    } // namespace core

} // namespace neo

#endif // NEO_CORE_HPP