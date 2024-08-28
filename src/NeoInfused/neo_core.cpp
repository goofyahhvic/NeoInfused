#include "neo_pch.hpp"
#include "NeoInfused/neo_core.hpp"

#include "NeoInfused/core/neo_window.hpp"

namespace neo {
	uint32_t SizeOf(Type type)
	{
		switch (type)
		{
		case Type::None:          return 0;
		case Type::Byte:          return 1;
		case Type::UByte:         return 1;
		case Type::Short:         return sizeof(short);
		case Type::UShort:        return sizeof(unsigned short);
		case Type::Int:           return sizeof(int);
		case Type::UInt:          return sizeof(unsigned int);
		case Type::Float:         return sizeof(float);
		case Type::Double:        return sizeof(double);
		}
		return UINT32_MAX;
	}

	std::string HoursMinutesSeconds(void)
	{
		std::time_t seconds = std::time(nullptr);
		std::string str(std::asctime(std::localtime(&seconds)));
		str = str.substr(10, 10);
		str[0] = '[';
		str[str.length() - 1] = ']';
		return str;
	}
	std::string YearMonthDay(void)
	{
		const std::chrono::year_month_day ymd{ std::chrono::floor<std::chrono::days>(std::chrono::system_clock::now()) };
		return NEO_FORMAT("[{0}]", ymd);
	}
	std::string DateAndTime(void)
	{
		std::time_t seconds = std::time(nullptr);
		std::string str(std::asctime(std::localtime(&seconds)));
		str = str.substr(11, 8);
		const std::chrono::year_month_day ymd{ std::chrono::floor<std::chrono::days>(std::chrono::system_clock::now()) };
		return NEO_FORMAT("[{0}][{1}]", ymd, str);
	}
	
	static std::string get_exec_path(void)
	{
	#if defined(NEO_PLATFORM_LINUX)
		return std::filesystem::canonical("/proc/self/exe").string();
	#elif defined(NEO_PLATFORM_WINDOWS)
		char exec_path_buffer[MAX_PATH];
		GetModuleFileNameA(nullptr, exec_path_buffer, MAX_PATH);
		return exec_path_buffer;
	#endif
	}

#define INDEX exec_path.find_last_of('/')

	static Core* _This = nullptr;
	Core& Core::Get(void) { return *_This; }

	Core::Core(int argc, char** argv)
	: argc(argc), argv(argv), version("Pre-Alpha"),
	exec_path(get_exec_path()), exec_dir(exec_path.substr(0, INDEX+1)),
	exec_name(exec_path.substr(INDEX+1, exec_path.find_last_of('.')))
	{
		NEO_ASSERT(!_This, "Already has initialized NeoInfused!");
		_This = this;
	#if !defined (NEO_CONFIG_DIST)
		NEO_DATE_TIME_LOG << '\n';
	#endif // NEO_CONFIG_DIST   
		NEO_INFO_LOG("Initializing NeoInfused version {}", version);

		NEO_ASSERT_FUNC(glfwInit(), "Failed to initialize glfw!");
		glfwSetErrorCallback([](int error, const char* description)
		{
			throw GLFWError(error, description);
		});

		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	}

	Core::~Core(void)
	{
		NEO_INFO_LOG("Shutting down NeoInfused, Goodbye!");

		glfwTerminate();

		_This = nullptr;
		NEO_LOG_NEWLINE;
	}

} // namespace neo
