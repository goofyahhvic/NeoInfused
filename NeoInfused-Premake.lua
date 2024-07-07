OUTPUT_DIR = "%{cfg.buildcfg}-%{cfg.system}"
INCLUDE_DIR = {}
LIB_DIR = {}

INCLUDE_DIR["external"] = "external/include/"
LIB_DIR["external"] = "external/lib/"

INCLUDE_DIR["submods"] = "submods/"

include "glad/glad-Premake.lua"

project "NeoInfused"
    location "./"
    targetname "NeoInfused-bin"
    kind "StaticLib"
    staticruntime "Off"

    language "C++"
    cppdialect "C++20"
    systemversion "latest"

    targetdir "bin/%{OUTPUT_DIR}/%{prj.name}/"
    objdir "bin-int/%{OUTPUT_DIR}/%{prj.name}/"

    pchheader "neo_pch.hpp"
    pchsource "src/neo_pch.cpp"

    files {
        "include/**.hpp",
        "src/**.hpp",
        "src/**.cpp",
    }
    includedirs {
        "include/",
        "%{INCLUDE_DIR.external}",
        "%{INCLUDE_DIR.submods}",
        "%{INCLUDE_DIR.glad}"
    }

    links {
        "glfw",
        "glad"
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

        includedirs { "%{INCLUDE_DIR.external}windows/" }
        libdirs { "%{LIB_DIR.external}windows/" }
    
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