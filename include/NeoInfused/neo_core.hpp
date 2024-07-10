#if !defined(NEO_CORE_HPP)
#define NEO_CORE_HPP

#include <stdint.h>

// F for Font
// B for Background
#define NEO_COLOR_RSET  "\x1B[0m"         // reset color
#define NEO_COLOR_FRED  "\x1B[31m"        // red
#define NEO_COLOR_BRED  "\x1B[0m\033[41m" // red
#define NEO_COLOR_FGRN  "\x1B[32m"        // green 
#define NEO_COLOR_FYEL  "\x1B[33m"        // yellow
#define NEO_COLOR_FBLU  "\x1B[34m"        // blue
#define NEO_COLOR_FMAG  "\x1B[35m"        // magenta
#define NEO_COLOR_FCYN  "\x1B[36m"        // cyan
#define NEO_COLOR_FWHT  "\x1B[37m"        // white

#define NEO_FONT_BOLD "\x1B[1m"           // bold
#define NEO_FONT_UNDL "\x1B[4m"           // underline

#define NEO_COLOR_BLACK {0, 0, 0, 1}
#define NEO_COLOR_RED   {1, 0, 0, 1}
#define NEO_COLOR_YEL   {1, 1, 0, 1}
#define NEO_COLOR_PURPL {1, 0, 1, 1}
#define NEO_COLOR_GREEN {0, 1, 0, 1}
#define NEO_COLOR_CYAN  {0, 1, 1, 1}
#define NEO_COLOR_BLUE  {0, 0, 1, 1}
#define NEO_COLOR_WHITE {1, 1, 1, 1}

#define NEO_FORMAT(...) std::format(__VA_ARGS__)

#if !defined(NEO_CONFIG_DIST)

    #define NEO_ASSERT(x, ...) if(!(x)) {\
                                throw std::runtime_error(NEO_FORMAT(__VA_ARGS__));\
                               }
    
    #define NEO_ASSERT_FUNC(x, ...) NEO_ASSERT(x, __VA_ARGS__);

#else
    #define NEO_ASSERT(x, ...)
    #define NEO_ASSERT_FUNC(x, ...) x;

#endif // NEO_CONFIG_DIST

#if defined(NEO_PLATFORM_LINUX)
    #define C_STR c_str()
#elif defined(NEO_PLATFORM_WINDOWS)
    #define C_STR string().c_str()
#endif // NEO_PLATFORM_LINUX

#if !defined(NEO_CONFIG_DIST)

    #define NEO_TRACE_LOG(...) std::cout << NEO_FORMAT(NEO_FONT_BOLD                "{0}[Neo]" NEO_COLOR_RSET " {1}\n", neo::HoursMinutesSeconds(), NEO_FORMAT(__VA_ARGS__)) 
    #define NEO_INFO_LOG(...)  std::cout << NEO_FORMAT(NEO_FONT_BOLD NEO_COLOR_FGRN "{0}[Neo]" NEO_COLOR_RSET " {1}\n", neo::HoursMinutesSeconds(), NEO_FORMAT(__VA_ARGS__)) 
    #define NEO_WARN_LOG(...)  std::cout << NEO_FORMAT(NEO_FONT_BOLD NEO_COLOR_FYEL "{0}[Neo]" NEO_COLOR_RSET " {1}\n", neo::HoursMinutesSeconds(), NEO_FORMAT(__VA_ARGS__)) 
    #define NEO_ERROR_LOG(...) std::cout << NEO_FORMAT(NEO_FONT_BOLD NEO_COLOR_FRED "{0}[Neo]" NEO_COLOR_RSET " {1}\n", neo::HoursMinutesSeconds(), NEO_FORMAT(__VA_ARGS__))
    #define NEO_FATAL_LOG(...) std::cout << NEO_FORMAT(NEO_FONT_BOLD NEO_COLOR_BRED "{0}[Neo]" NEO_COLOR_RSET " {1}\n", neo::HoursMinutesSeconds(), NEO_FORMAT(__VA_ARGS__))

    #define NEO_FULL_LOG(...)  std::cout << NEO_FORMAT(NEO_FONT_BOLD NEO_COLOR_FGRN "{0}"      NEO_COLOR_RSET "\n",     neo::DateAndTime(), NEO_FORMAT(__VA_ARGS__)) 
    #define NEO_DATE_LOG       std::cout << NEO_FORMAT(NEO_FONT_BOLD NEO_COLOR_FGRN "{0}"      NEO_COLOR_RSET "\n",     neo::YearMonthDay()) 
    #define NEO_TIME_LOG       std::cout << NEO_FORMAT(NEO_FONT_BOLD NEO_COLOR_FGRN "{0}"      NEO_COLOR_RSET "\n",     neo::HoursMinutesSeconds()) 
    #define NEO_DATE_TIME_LOG  std::cout << NEO_FORMAT(NEO_FONT_BOLD NEO_COLOR_FGRN "{0}[{1}]" NEO_COLOR_RSET "\n",     neo::DateAndTime(), std::chrono::current_zone()->name()) 
    #define NEO_LOG_NEWLINE    std::cout << '\n';
#else
    #define NEO_TRACE_LOG(...)
    #define NEO_INFO_LOG(...)
    #define NEO_WARN_LOG(...)
    #define NEO_ERROR_LOG(...)
    #define NEO_FATAL_LOG(...)

    #define NEO_FULL_LOG(...)
    #define NEO_DATE_LOG       
    #define NEO_TIME_LOG       
    #define NEO_DATE_TIME_LOG  
    #define NEO_LOG_NEWLINE    

#endif // NEO_CONFIG_DIST
#define NEO_LOG_CONTINUE "\n\t\t"

#define NEO_BIT(x) (1u << x)

enum neoRendererAPI;

namespace neo {
    using byte_t = char;

    std::string HoursMinutesSeconds(void);
    std::string YearMonthDay(void);
    std::string DateAndTime(void);
 
    inline int32_t Round32(float num) { return (int32_t)floor(num + 0.5f); }
    inline int64_t Round64(double num) { return (int64_t)floor(num + 0.5f); }

    struct InitInfo {
        int argc;
        char** argv;
        neoRendererAPI renderer_api;
    };

    class GLFWError : public std::exception {
    public:
        GLFWError(int error, const char* description) : m_Msg(NEO_FORMAT("GLFW Error #{0}: {1}", error, description)) {}
        inline const char* what(void) const noexcept override { return m_Msg.c_str(); }
    private:
        std::string m_Msg;
    };

    class Core {
        Core(void) = default;
        ~Core(void) = default;
    public:
        static void Init(const InitInfo& info);
        static void Terminate();

        static inline const std::string& GetExecPath(void) { return m_ExecPath; }
        static inline const std::string& GetExecDir(void) { return m_ExecDir; }
        static inline const std::string& GetExecName(void) { return m_ExecName; }

        static int    argc(void) { return m_Argc; }
        static char** argv(void) { return m_Argv; }
    private:
        static int m_Argc;
        static char** m_Argv;
        static std::string m_ExecPath, m_ExecDir, m_ExecName;
    };
} // namespace neo

#endif // NEO_CORE_HPP