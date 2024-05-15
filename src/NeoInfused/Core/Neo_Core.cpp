#include "Neo_PCH.hpp"
#include "./Neo_Core.hpp"

#include "Engine/Neo_App.hpp"
#include "Engine/Sprite/Neo_SpriteRegistry.hpp"

namespace neo {
    using namespace core;
    int         Internal::_argc;
    char**      Internal::_argv;
    String      Internal::error;
#if defined(NEO_PLATFORM_LINUX)
    std::string Internal::exec_path, Internal::exec_folder, Internal::exec_name;
#elif defined(NEO_PLATFORM_WINDOWS)

#endif // NEO_PLATFORM_LINUX

    App* core::GetApplication(void) { return App::Get(); }
    size_t core::get_str_size(const char* str) {
        size_t i = 1;
        for (const char* it; *it != '\0'; it++) {
            i++;
        }
        return i;
    }

    int32_t Internal::Init(int argc, char* argv[]) {
        _argc = argc;
        _argv = argv;

#if defined(NEO_PLATFORM_LINUX)

        exec_name = "";
        std::ifstream("/proc/self/comm") >> exec_name;

        exec_path = std::filesystem::canonical("/proc/self/exe").string();

        size_t index = exec_path.find(exec_name);
        exec_folder = exec_path.substr(0, index);

        if (exec_path.empty() || exec_folder.empty() || exec_name.empty()) {
            error = String("Error in getting executable path!");
            return NEO_FAILURE;
        }

#elif defined(NEO_PLATFORM_WINDOWS)


#endif // NEO_PLATFORM_LINUX
        SpriteRegistry::Init();

        return NEO_SUCCESS;
    }

    void Internal::Terminate() {
        SpriteRegistry::Terminate();
    }
} // namespace neo
