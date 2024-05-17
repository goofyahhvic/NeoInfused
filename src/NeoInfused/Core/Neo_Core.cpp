#include "Neo_PCH.hpp"
#include "NeoInfused/Core/Neo_Core.hpp"

#include "NeoInfused/Neo_App.hpp"
#include "NeoInfused/Sprite/Neo_SpriteRegistry.hpp"

namespace neo {
    using namespace neo_core;
    int              Internal::_argc;
    char**           Internal::_argv;
    neo_core::String Internal::error;
#if defined(NEO_PLATFORM_LINUX)
    std::string Internal::exec_path, Internal::exec_folder, Internal::exec_name;
#elif defined(NEO_PLATFORM_WINDOWS)

#endif // NEO_PLATFORM_LINUX

    int32_t Internal::Init(int argc, char* argv[]) {
        _argc = argc;
        _argv = argv;

#if defined(NEO_PLATFORM_LINUX)

        exec_name.clear();
        std::ifstream("/proc/self/comm") >> exec_name;

        exec_path = std::filesystem::canonical("/proc/self/exe").string();

        size_t index = exec_path.find(exec_name);
        exec_folder = exec_path.substr(0, index);

        if (exec_path.empty() || exec_folder.empty() || exec_name.empty()) {
            error = neo_core::String("Error in getting executable path!\0");
            return NEO_FAILURE;
        }

#elif defined(NEO_PLATFORM_WINDOWS)


#endif // NEO_PLATFORM_LINUX

        SpriteRegistry::Init();

        return NEO_SUCCESS;
    }

    void Internal::Terminate() {
        SpriteRegistry::Reset();
    }
} // namespace neo
