INCLUDE_DIR["glad"] = "glad/include/"

project "glad"
    location "./"
    targetname "glad-bin"
    kind "StaticLib"
    staticruntime "Off"

    language "C"
    cdialect "C17"
    systemversion "latest"

    targetdir "bin/%{OUTPUT_DIR}/%{prj.name}/"
    objdir "bin-int/%{OUTPUT_DIR}/%{prj.name}/"

    files {
        "include/glad/glad.h",
        "include/KHR/khrplatform.h",
        "src/glad.c"
    }
    includedirs {
        "include/"
    }

    filter "system:linux"
        toolset "gcc"
        defines { "NEO_PLATFORM_LINUX" }

    filter "system:windows"
        toolset "msc"
        defines {
            "NEO_PLATFORM_WINDOWS",
            "_CRT_SECURE_NO_WARNINGS"
        }
    
    filter "configurations:dbg"
        symbols "On"
        runtime "Debug"
    filter "configurations:rel"
        optimize "speed"
        symbols "Off"
        runtime "Release"
    filter "configurations:dist"
        optimize "speed"
        symbols "Off"
        runtime "Release"