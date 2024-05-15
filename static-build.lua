OUTPUT_DIR = "%{cfg.buildcfg}-%{cfg.system}"
INCLUDE_DIR = {}
LIB_DIR = {}

INCLUDE_DIR["external"] = "external/include/"
LIB_DIR["external"] = "external/lib/"

project "NeoInfused"
    location "%{prj.name}/"
    targetname "%{prj.name}Lib"
    kind "StaticLib"
    staticruntime "off"

    language "C++"
    systemversion "latest"

    targetdir("bin/" ..  OUTPUT_DIR .. "/%{prj.name}/")
    objdir("bin-int/" ..  OUTPUT_DIR .. "/%{prj.name}/")

    pchheader "Neo_PCH.hpp"
    pchsource "src/Neo_PCH.cpp"

    files {
        "src/**.hpp",
		"src/**.h",
        "src/**.cpp",
		"src/**.c",

        "include/**.hpp",
		"include/**.h",
        "include/**.cpp",
		"include/**.c"
    }

    includedirs {
        "src/",
        "include/",
        "src/NeoInfused",
        "include/NeoInfused",
        "%{INCLUDE_DIR.external}"
    }

    filter "system:linux"
        toolset "gcc"
        cppdialect "C++17"

        defines {
            "NEO_PLATFORM_LINUX"
        }

        links {
            "SDL2",
            "SDL2_image",
            "SDL2_ttf",
            --"SDL2_mixer",
            --"SDL2_net",
            "fmt"
        }
    filter "system:windows"
        toolset "msc"
        cppdialect "C++20"

        defines {
            "NEO_PLATFORM_WINDOWS",
            "_CRT_SECURE_NO_WARNINGS"
        }

        libdirs {
            "%{LIB_DIR.external}windows"
        }

        links {
            "SDL2",
            "SDL2main",
            "SDL2_image",
            "SDL2_ttf",
            --"SDL2_mixer",
            --"SDL2_net",
            "SDL2test"
        }

    filter "configurations:dbg"
        symbols "On"
        defines {
            "NEO_CONFIG_DEBUG"
        }
    filter "configurations:rel"
        optimize "speed"
        symbols "off"
        defines {
            "NEO_CONFIG_RELEASE"
        }
    filter "configurations:dist"
        optimize "speed"
        symbols "off"
        defines {
            "NEO_CONFIG_DIST"
        }