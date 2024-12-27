#include "neo_pch.hpp"
#include "NeoInfused/neo_core.hpp"

#include "NeoInfused/core/neo_utils.hpp"
#include "influx/inf_loader.hpp"

namespace neo {
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
	
	static std::filesystem::path getExecPath(void)
	{
	#if defined(NEO_PLATFORM_LINUX)
		return std::filesystem::canonical("/proc/self/exe");
	#elif defined(NEO_PLATFORM_WINDOWS)
		char exec_path_buffer[MAX_PATH];
		GetModuleFileNameA(nullptr, exec_path_buffer, MAX_PATH);
		return exec_path_buffer;
	#endif
	}

#define INDEX initData->exec_path.find_last_of('/')

	struct init_data_t {
		inf::renderer_api_t api;
		std::filesystem::path exec_path, exec_dir, exec_name;
		std::string_view version;
	};
	static init_data_t* initData = nullptr;

	void InitCore(void)
	{
		NEO_ASSERT(!initData, "Already has initialized NeoInfused!");
		initData = tmalloc<init_data_t>(1);

		initData->api = INF_API_VULKAN;

		new (&(initData->version)) std::string_view("Pre-Alpha");

		new (&(initData->exec_path)) std::filesystem::path(getExecPath());
		new (&(initData->exec_dir))  std::filesystem::path(initData->exec_path.parent_path());
		new (&(initData->exec_name)) std::filesystem::path(initData->exec_path.filename());

	#if !defined (NEO_CONFIG_DIST)
		NEO_DATE_TIME_LOG << '\n';
	#endif // NEO_CONFIG_DIST   
		NEO_INFO_LOG("Initializing NeoInfused version {}", initData->version);

		inf::Loader::Load(initData->api);

		glfwSetErrorCallback([](int error, const char* description)
		{
			NEO_ERROR_LOG("GLFW Error#{}: {}", error, description);
			throw std::runtime_error(NEO_FORMAT("GLFW Error #{}", error));
		});
		NEO_ASSERT_FUNC(glfwInit(), "Failed to initialize glfw!");
		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	}

	void ShutdownCore(void)
	{
		NEO_INFO_LOG("Shutting down NeoInfused, Goodbye!");

		inf::ShutdownAPI();
		glfwTerminate();

		inf::Loader::Unload();

		initData->exec_path.~path();
		initData->exec_name.~path();
		initData->exec_dir.~path();
		free(initData);
		initData = nullptr;
	}

	const std::filesystem::path& ExecPath(void)
	{
		return initData->exec_path;
	}

	const std::filesystem::path& ExecDir(void)
	{
		return initData->exec_dir;
	}

	const std::filesystem::path& ExecName(void)
	{
		return initData->exec_name;
	}

} // namespace neo
