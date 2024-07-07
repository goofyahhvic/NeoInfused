INCLUDE_DIR["glad"] = "dependencies/glad/include/"

project "glad"
    location "./"
    targetname "glad-bin"
    kind "StaticLib"
    staticruntime "Off"

    language "C"
    cdialect "C17"
    systemversion "latest"

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