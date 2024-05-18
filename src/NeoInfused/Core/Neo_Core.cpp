#include "Neo_PCH.hpp"
#include "NeoInfused/Core/Neo_Core.hpp"

#include "NeoInfused/Neo_App.hpp"
#include "NeoInfused/Sprite/Neo_SpriteRegistry.hpp"

namespace neo {
    using namespace neo_core;
    int    Internal::_argc;
    char** Internal::_argv;
    neo_core::StringConst Internal::error;
    std::string Internal::exec_path, Internal::exec_folder, Internal::exec_name;

    int32_t Internal::Init(int argc, char* argv[]) {
        _argc = argc;
        _argv = argv;

        exec_path.clear();
        exec_name.clear();
        exec_folder.clear();

#if defined(NEO_PLATFORM_LINUX)
        exec_path = std::filesystem::canonical("/proc/self/exe").string();

        index_t index = exec_path.find_last_of('/');
        exec_folder = exec_path.substr(0, index+1);
        exec_name = exec_path.substr(index+1);

#elif defined(NEO_PLATFORM_WINDOWS)
        char exec_path_buffer[MAX_PATH];
        GetModuleFileNameA(nullptr, exec_path_buffer, MAX_PATH);
        exec_path = std::string(exec_path_buffer);
        
        index_t index = exec_path.find_last_of('\\');
        exec_folder = exec_path.substr(0, index+1);
        exec_name = exec_path.substr(index+1);
#endif // NEO_PLATFORM_LINUX

        if (exec_path.empty() || exec_folder.empty() || exec_name.empty()) {
            error = neo_core::StringConst("Error in getting executable path!");
            return NEO_FAILURE;
        }

        SpriteRegistry::Init();

        return NEO_SUCCESS;
    }

    void Internal::Terminate() {
        SpriteRegistry::Reset();
    }
} // namespace neo
