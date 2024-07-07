#include "neo_pch.hpp"
#include "NeoInfused/neo_core.hpp"

#include "NeoInfused/core/neo_window.hpp"
#include "NeoInfused/graphics/neo_context.hpp"

namespace neo {
    int    Core::m_Argc;
    char** Core::m_Argv;
    std::string Core::m_ExecPath, Core::m_ExecDir;

    std::string hours_minutes_seconds(void) {
        std::time_t seconds = std::time(nullptr);
        std::string str(std::asctime(std::localtime(&seconds)));
        str = str.substr(10, 10);
        str[0] = '[';
        str[str.length()-1] = ']';
        return str;
    }
    std::string year_month_day(void) {
        const std::chrono::year_month_day ymd {std::chrono::floor<std::chrono::days>(std::chrono::system_clock::now())};
        return NEO_FORMAT("[{0}]", ymd);
    }
    std::string year_month_day_hours_minutes_seconds(void) {
        std::time_t seconds = std::time(nullptr);
        std::string str(std::asctime(std::localtime(&seconds)));
        str = str.substr(11, 8);
        const std::chrono::year_month_day ymd {std::chrono::floor<std::chrono::days>(std::chrono::system_clock::now())};
        return NEO_FORMAT("[{0}][{1}]", ymd, str);
    }

    void Core::Init(const InitInfo& info) {
    #if !defined (NEO_CONFIG_DIST)
        NEO_DATE_TIME_LOG << '\n';
    #endif // NEO_CONFIG_DIST   
        NEO_INFO_LOG("Initializing NeoInfused!");
        Core::m_Argc = info.argc;
        Core::m_Argv = info.argv;
        Context::m_API = info.renderer_api;

#if defined(NEO_PLATFORM_LINUX)
        Core::m_ExecPath = std::filesystem::canonical("/proc/self/exe").string();
        size_t index = Core::m_ExecPath.find_last_of('/');
#elif defined(NEO_PLATFORM_WINDOWS)
        char exec_path_buffer[MAX_PATH];
        GetModuleFileNameA(nullptr, exec_path_buffer, MAX_PATH);

        Core::m_ExecPath = std::string(exec_path_buffer);
        size_t index = Core::m_ExecPath.find_last_of('\\');
#endif // NEO_PLATFORM_LINUX
        Core::m_ExecDir = Core::m_ExecPath.substr(0, index+1);

        if (Core::m_ExecPath.empty() || Core::m_ExecDir.empty()) {
            throw std::runtime_error("Error in getting executable path!");
        }

        NEO_ASSERT_FUNC(glfwInit(), "Failed to initialize glfw!");
        glfwSetErrorCallback([](int error, const char* description) {
            throw GLFWError(error, description);
        });

        if (info.renderer_api == NEO_RENDERERAPI_OPENGL) {
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
			Context::Create_GL();
        }
    }

    void Core::Terminate(void) {
        NEO_INFO_LOG("Terminating NeoInfused, Goodbye!");

        if (!Window::m_Windows.empty()) {
            for (const auto& [id, window] : Window::m_Windows) {
                glfwDestroyWindow(window->m_Window);
                delete window;
            }
            Window::m_Windows.clear();
        }

        Context::Get()->terminate();
        Context::Destroy();
        glfwTerminate();

        NEO_LOG_NEWLINE;
    }
} // namespace neo
