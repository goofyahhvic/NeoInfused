INCLUDE_DIR["GLFW"] = "dependencies/glfw/include/"

project "GLFW"
    location "./glfw/"
    targetname "GLFW-bin"
    kind "StaticLib"
    staticruntime "Off"

    language "C"
    cdialect "C17"
    systemversion "latest"

    files {
		"glfw/include/GLFW/glfw3.h",
		"glfw/include/GLFW/glfw3native.h",
		"glfw/src/context.c",
		"glfw/src/init.c",
		"glfw/src/input.c",
		"glfw/src/monitor.c",
		"glfw/src/null_init.c",
		"glfw/src/null_joystick.c",
		"glfw/src/null_monitor.c",
		"glfw/src/null_window.c",
		"glfw/src/platform.c",
		"glfw/src/vulkan.c",
		"glfw/src/window.c",
	}

	filter "system:linux"
        toolset "gcc"
		pic "On"
		files {
			"glfw/src/x11_init.c",
			"glfw/src/x11_monitor.c",
			"glfw/src/x11_window.c",
			"glfw/src/xkb_unicode.c",
			"glfw/src/posix_module.c",
			"glfw/src/posix_poll.c",
			"glfw/src/posix_time.c",
			"glfw/src/posix_thread.c",
			"glfw/src/posix_module.c",
			"glfw/src/glx_context.c",
			"glfw/src/egl_context.c",
			"glfw/src/osmesa_context.c",
			"glfw/src/linux_joystick.c"
		}

		defines {
			"_GLFW_X11",
			"_XOPEN_SOURCE 700",
			"_GNU_SOURCE"
		}

    filter "system:windows"
        toolset "msc"
		files {
			"glfw/src/win32_init.c",
			"glfw/src/win32_joystick.c",
			"glfw/src/win32_module.c",
			"glfw/src/win32_monitor.c",
			"glfw/src/win32_time.c",
			"glfw/src/win32_thread.c",
			"glfw/src/win32_window.c",
			"glfw/src/wgl_context.c",
			"glfw/src/egl_context.c",
			"glfw/src/osmesa_context.c"
		}

		defines { 
			"_GLFW_WIN32",
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