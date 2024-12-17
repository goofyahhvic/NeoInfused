INCLUDE_DIR["inf"] = "Influx/include/"
VULKAN_SDK = os.getenv("VULKAN_SDK")

project "InfluxRenderer"
    location "./"
    targetname "%{prj.name}-bin"
    kind "StaticLib"
    staticruntime "Off"

    language "C++"
    cppdialect "C++20"
    systemversion "latest"

    pchheader "inf_pch.hpp"
    pchsource "src/inf_pch.cpp"

    files {
        "include/**.hpp",
        "src/**.hpp",
        "src/**.cpp"
    }

    includedirs {
        "include/",
        "../include/",
        "../%{INCLUDE_DIR.GLFW}",
        "../%{INCLUDE_DIR.glm}"
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
        symbols "off"
        runtime "Release"
        defines { "NEO_CONFIG_RELEASE" }
    filter "configurations:dist"
        optimize "speed"
        symbols "off"
        runtime "Release"
        defines { "NEO_CONFIG_DIST" }

project "Influx-vk"
    location "vk"
    targetname "%{prj.name}-bin"
    kind "SharedLib"
    staticruntime "Off"

    language "C++"
    cppdialect "C++20"
    systemversion "latest"

    pchheader "vk_pch.hpp"
    pchsource "vk/vk_pch.cpp"

    files {
        "vk/**.hpp",
        "vk/**.cpp"
    }

    includedirs {
        "include/",
        "../include/",
        "vk/",
        "../%{INCLUDE_DIR.GLFW}",
        "../%{INCLUDE_DIR.glm}"
    }
	links {
		"GLFW"
	}

    filter "system:linux"
        toolset "gcc"
        defines { "NEO_PLATFORM_LINUX" }
		
		links {
			"vulkan"
		}
    filter "system:windows"
        toolset "msc"
        defines {
            "NEO_PLATFORM_WINDOWS",
            "_CRT_SECURE_NO_WARNINGS"
        }
		
		includedirs {
			"%{VULKAN_SDK}/Include"
		}
		libdirs {
			"%{VULKAN_SDK}/Lib"
		}
		links {
			"vulkan-1"
		}

    filter "configurations:dbg"
        symbols "On"
        runtime "Debug"
        defines { "NEO_CONFIG_DEBUG" }
    filter "configurations:rel"
        optimize "speed"
        symbols "off"
        runtime "Release"
        defines { "NEO_CONFIG_RELEASE" }
    filter "configurations:dist"
        optimize "speed"
        symbols "off"
        runtime "Release"
        defines { "NEO_CONFIG_DIST" }

