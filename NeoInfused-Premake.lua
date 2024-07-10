INCLUDE_DIR = {}
LIB_DIR = {}

include "dependencies/glad/glad-Premake.lua"
include "dependencies/GLFW-Premake.lua"
INCLUDE_DIR["glm"] = "dependencies/glm/include/"

project "NeoInfused"
    location "./"
    targetname "NeoInfused-bin"
    kind "StaticLib"
    staticruntime "Off"

    language "C++"
    cppdialect "C++20"
    systemversion "latest"

    pchheader "neo_pch.hpp"
    pchsource "src/neo_pch.cpp"

    files {
        "include/**.hpp",
        "include/**.h",
        "src/**.hpp",
        "src/**.h",
        "src/**.cpp"
    }
    includedirs {
        "include/",
        "%{INCLUDE_DIR.GLFW}",
        "%{INCLUDE_DIR.glad}",
        "%{INCLUDE_DIR.glm}"
    }

    links {
        "glad",
        "GLFW"
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
        defines { "NEO_CONFIG_DEBUG" }
    filter "configurations:rel"
        optimize "speed"
        symbols "Off"
        runtime "Release"
        defines { "NEO_CONFIG_RELEASE" }
    filter "configurations:dist"
        optimize "speed"
        symbols "Off"
        runtime "Release"
        defines { "NEO_CONFIG_DIST" }