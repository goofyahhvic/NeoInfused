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

#define NEO_FORMAT std::format

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
#define C_STR c_str
#elif defined(NEO_PLATFORM_WINDOWS)
#define C_STR string().c_str
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

using namespace std::chrono_literals;

namespace inf { using renderer_api_t = unsigned char; }

namespace neo {
	using byte_t = unsigned char;

	enum class Type: unsigned char {
		None = 0,
		Byte,        UByte,
		Char = Byte, UChar = UByte,
		Int8 = Byte, UInt8 = UByte,
		Int16,       UInt16,
		Int32,       UInt32,
		Int64,       UInt64,
		Float,
		Double
	};
	uint32_t SizeOf(Type type);

	template<typename T>
	inline T* tmalloc(size_t size)
	{
		return (T*)malloc(size * sizeof(T));
	}

	template<typename T>
	inline T* trealloc(T* buffer, size_t size)
	{
		return (T*)realloc(buffer, size * sizeof(T));
	}

	std::string HoursMinutesSeconds(void);
	std::string YearMonthDay(void);
	std::string DateAndTime(void);

	inline int32_t Round32(float num) { return (int32_t)floor(num + 0.5f); }
	inline int64_t Round64(double num) { return (int64_t)floor(num + 0.5f); }

	void Init(void);
	void Shutdown(void);

	const std::filesystem::path& ExecPath(void);
	const std::filesystem::path& ExecDir(void);
	const std::filesystem::path& ExecName(void);

} // namespace neo

#endif // NEO_CORE_HPP