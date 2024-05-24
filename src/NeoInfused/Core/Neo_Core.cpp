#include "Neo_PCH.hpp"
#include "NeoInfused/Core/Neo_Core.hpp"

#include "NeoInfused/Neo_App.hpp"

namespace neo {
    int    Core::m_Argc;
    char** Core::m_Argv;
    std::string Core::m_ExecPath, Core::m_ExecDir;

    void Core::Init(const InitInfo& info) {
        NEO_INFO_LOG("Initializing NeoInfused!");
        Core::m_Argc = info.argc;
        Core::m_Argv = info.argv;

#if defined(NEO_PLATFORM_LINUX)
        Core::m_ExecPath = std::filesystem::canonical("/proc/self/exe").string();
        index_t index = Core::m_ExecPath.find_last_of('/');
#elif defined(NEO_PLATFORM_WINDOWS)
        char exec_path_buffer[MAX_PATH];
        GetModuleFileNameA(nullptr, exec_path_buffer, MAX_PATH);

        Core::m_ExecPath = std::string(exec_path_buffer);
        index_t index = Core::m_ExecPath.find_last_of('\\');
#endif // NEO_PLATFORM_LINUX
        Core::m_ExecDir = Core::m_ExecPath.substr(0, index+1);

        if (Core::m_ExecPath.empty() || Core::m_ExecDir.empty()) {
            throw std::runtime_error("Error in getting executable path!");
        }

        Renderer::Init();

        NEO_ASSERT_FUNC(!SDL_Init(SDL_INIT_EVERYTHING), "Failed to initialize SDL: {0}", SDL_GetError());
        SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "nearest");
        IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);
    }
    void Core::Init(int argc, char** argv) {
        Core::Init({argc, argv, 1000});
    }

    void Core::Terminate(void) {
        NEO_INFO_LOG("Terminating NeoInfused, Goodbye!");
        IMG_Quit();
        SDL_Quit();
    }
} // namespace neo
