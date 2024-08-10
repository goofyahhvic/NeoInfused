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

#define NEO_TRACE_LOG(...) std::clog << NEO_FORMAT(NEO_FONT_BOLD                "{0}[Neo]" NEO_COLOR_RSET " {1}\n", neo::HoursMinutesSeconds(), NEO_FORMAT(__VA_ARGS__)) 
#define NEO_INFO_LOG(...)  std::clog << NEO_FORMAT(NEO_FONT_BOLD NEO_COLOR_FGRN "{0}[Neo]" NEO_COLOR_RSET " {1}\n", neo::HoursMinutesSeconds(), NEO_FORMAT(__VA_ARGS__)) 
#define NEO_WARN_LOG(...)  std::clog << NEO_FORMAT(NEO_FONT_BOLD NEO_COLOR_FYEL "{0}[Neo]" NEO_COLOR_RSET " {1}\n", neo::HoursMinutesSeconds(), NEO_FORMAT(__VA_ARGS__)) 
#define NEO_ERROR_LOG(...) std::clog << NEO_FORMAT(NEO_FONT_BOLD NEO_COLOR_FRED "{0}[Neo]" NEO_COLOR_RSET " {1}\n", neo::HoursMinutesSeconds(), NEO_FORMAT(__VA_ARGS__))
#define NEO_FATAL_LOG(...) std::clog << NEO_FORMAT(NEO_FONT_BOLD NEO_COLOR_BRED "{0}[Neo]" NEO_COLOR_RSET " {1}\n", neo::HoursMinutesSeconds(), NEO_FORMAT(__VA_ARGS__))

#define NEO_FULL_LOG(...)  std::clog << NEO_FORMAT(NEO_FONT_BOLD NEO_COLOR_FGRN "{0}"      NEO_COLOR_RSET "\n",     neo::DateAndTime(), NEO_FORMAT(__VA_ARGS__)) 
#define NEO_DATE_LOG       std::clog << NEO_FORMAT(NEO_FONT_BOLD NEO_COLOR_FGRN "{0}"      NEO_COLOR_RSET "\n",     neo::YearMonthDay()) 
#define NEO_TIME_LOG       std::clog << NEO_FORMAT(NEO_FONT_BOLD NEO_COLOR_FGRN "{0}"      NEO_COLOR_RSET "\n",     neo::HoursMinutesSeconds()) 
#define NEO_DATE_TIME_LOG  std::clog << NEO_FORMAT(NEO_FONT_BOLD NEO_COLOR_FGRN "{0}[{1}]" NEO_COLOR_RSET "\n",     neo::DateAndTime(), std::chrono::current_zone()->name()) 
#define NEO_LOG_NEWLINE    std::clog << '\n';
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

enum neo_RendererAPI;

namespace neo {
	using byte_t = char;
	union color32 {
		struct { uint8_t r, g, b, a; };
		uint32_t rgba;
	};

	enum class Type {
		None = 0,
		Byte = 0x1400, UByte = 0x1401,
		Short = 0x1402, UShort = 0x1403,
		Int = 0x1404, UInt = 0x1405,
		Float = 0x1406, Double = 0x140A
	};
	uint32_t SizeOf(Type type);

	std::string HoursMinutesSeconds(void);
	std::string YearMonthDay(void);
	std::string DateAndTime(void);

	inline int32_t Round32(float num) { return (int32_t)floor(num + 0.5f); }
	inline int64_t Round64(double num) { return (int64_t)floor(num + 0.5f); }

	struct InitInfo {
		int argc;
		char** argv;
		neo_RendererAPI renderer_api;
	};

	class GLFWError : public std::exception {
	public:
		GLFWError(int error, const char* description) : m_Msg(NEO_FORMAT("GLFW Error #{0}: {1}", error, description)) {}
		inline const char* what(void) const noexcept override { return m_Msg.c_str(); }
	private:
		std::string m_Msg;
	};

	class Core {
	public:
		static inline Core& Get(void) { return *s_This; }
		inline const std::string& exec_path(void) const { return m_ExecPath; }
		inline const std::string& exec_dir(void) const { return m_ExecDir; }
		inline const std::string& exec_name(void) const { return m_ExecName; }
		inline const std::string& version(void) const { return m_Version; }

		int    argc(void) const { return m_Argc; }
		char** argv(void) { return m_Argv; }
	private:
		friend class App;
		Core(const InitInfo& info);
		~Core(void);
	private:
		int m_Argc;
		char** m_Argv;
		std::string m_ExecPath, m_ExecDir, m_ExecName, m_Version;

		static inline Core* s_This = nullptr;
	};
} // namespace neo

#endif // NEO_CORE_HPP