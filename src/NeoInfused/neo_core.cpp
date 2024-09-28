#include "neo_pch.hpp"
#include "NeoInfused/neo_core.hpp"

#include "NeoInfused/core/neo_window.hpp"
#include "influx/inf_loader.hpp"

namespace neo {
	uint32_t SizeOf(Type type)
	{
		switch (type)
		{
		case Type::None:   return 0u;
		case Type::Int8:   return 1u;
		case Type::UInt8:  return 1u;
		case Type::Int16:  return 2u;
		case Type::UInt16: return 2u;
		case Type::Int32:  return 4u;
		case Type::UInt32: return 4u;
		case Type::Int64:  return 8u;
		case Type::UInt64: return 8u;
		case Type::Float:  return sizeof(float);
		case Type::Double: return sizeof(double);
		default:           return 0u;
		}
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
	
	static std::string getExecPath(void)
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
	exec_path(getExecPath()), exec_dir(exec_path.substr(0, INDEX+1)),
	exec_name(exec_path.substr(INDEX+1, exec_path.find_last_of('.')))
	{
		NEO_ASSERT(!_This, "Already has initialized NeoInfused!");
		_This = this;
	#if !defined (NEO_CONFIG_DIST)
		NEO_DATE_TIME_LOG << '\n';
	#endif // NEO_CONFIG_DIST   
		NEO_INFO_LOG("Initializing NeoInfused version {}", version);

		glfwSetErrorCallback([](int error, const char* description)
		{
			NEO_ERROR_LOG("GLFW Error#{}: {}", error, description);
			throw std::runtime_error(NEO_FORMAT("GLFW Error #{}", error));
		});
		NEO_ASSERT_FUNC(glfwInit(), "Failed to initialize glfw!");
		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	}

	Core::~Core(void)
	{
		NEO_INFO_LOG("Shutting down NeoInfused, Goodbye!");

		inf::ShutdownAPI();
		glfwTerminate();

		_This = nullptr;
		NEO_LOG_NEWLINE;
	}

} // namespace neo
