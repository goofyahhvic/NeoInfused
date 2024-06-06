OUTPUT_DIR = "%{cfg.buildcfg}-%{cfg.system}"
INCLUDE_DIR = {}
LIB_DIR = {}

INCLUDE_DIR["external"] = "external/include/"
LIB_DIR["external"] = "external/lib/"

INCLUDE_DIR["submods"] = "submods/"

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

    pchheader "Neo_PCH.hpp"
    pchsource "src/Neo_PCH.cpp"

    files {
        "include/**.hpp",
        "src/**.hpp",
        "src/**.cpp",
    }
    includedirs {
        "src/",
        "include/",
        "%{INCLUDE_DIR.external}",
        "%{INCLUDE_DIR.submods}",
    }

    links {
        "SDL2",
        "SDL2_image",
        "SDL2_ttf",
        "SDL2_mixer"
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
        links { "SDL2test" }
    
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