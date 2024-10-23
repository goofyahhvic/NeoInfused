#include "neo_pch.hpp"
#include "NeoInfused/core/neo_window.hpp"

#include "NeoInfused/core/neo_app.hpp"
#include "influx/inf_loader.hpp"

namespace neo {
	window_t::window_t(uint32_t width, uint32_t height, const char* title)
	: m_Window(glfwCreateWindow(width, height, title, nullptr, nullptr)),
	m_Width(width), m_Height(height),
	surface(m_Window)
	{
		NEO_ASSERT(m_Window, "Failed to create glfw window!");
		NEO_ASSERT(surface, "Failed to create window surface!");
		glfwSetWindowUserPointer(m_Window, this);

		window_t::_SetGLFWCallbacks(m_Window);
	}
	void window_t::destroy(void)
	{
		surface.destroy();
		glfwDestroyWindow(m_Window);
		m_Window = nullptr;
	}

	void window_t::focus(void)
	{
		glfwFocusWindow(m_Window);
	}

	void window_t::set_size(uint32_t width, uint32_t height)
	{
		glfwSetWindowSize(m_Window, width, height);
		m_Width = width;
		m_Height = height;
	}
	void window_t::set_title(const char* title)
	{
		glfwSetWindowTitle(m_Window, title);
	}

	const char* window_t::title(void) const
	{
		return glfwGetWindowTitle(m_Window);
	}

	void window_t::_SetGLFWCallbacks(GLFWwindow* _window)
	{
		glfwSetKeyCallback(_window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			switch (action)
			{
			case GLFW_PRESS:
				GetEventQueue().emplace(event::key_pressed_t{
					NEO_KEY_PRESSED_EVENT,
					((window_t*)glfwGetWindowUserPointer(window)),
					false,
					(uint16_t)key,
					false
				});
				break;
			case GLFW_REPEAT:
				GetEventQueue().emplace(event::key_pressed_t {
					NEO_KEY_PRESSED_EVENT,
					((window_t*)glfwGetWindowUserPointer(window)),
					false,
					(uint16_t)key,
					true
				});
				break;
			case GLFW_RELEASE:
				GetEventQueue().emplace(event::key_released_t {
					NEO_KEY_RELEASED_EVENT,
					((window_t*)glfwGetWindowUserPointer(window)),
					false,
					(uint16_t)key
				});
				break;
			}
		});
		glfwSetWindowSizeCallback(_window, [](GLFWwindow* window, int width, int height)
		{
			window_t* __window = (window_t*)glfwGetWindowUserPointer(window);
			__window->m_Width = width;
			__window->m_Height = height;
			GetEventQueue().emplace(event::window_resize_t{
				NEO_WINDOW_RESIZE_EVENT,
				__window,
				false,
				(uint32_t)width, (uint32_t)height
			});
		});
		glfwSetWindowCloseCallback(_window, [](GLFWwindow* window)
		{
			window_t* __window = (window_t*)glfwGetWindowUserPointer(window);
			__window->should_close = true;
			GetEventQueue().emplace(event::window_close_t{
				NEO_WINDOW_CLOSE_EVENT,
				__window,
				false
			});
		});
		glfwSetWindowFocusCallback(_window, [](GLFWwindow* window, int focus)
		{
			window_t* __window = (window_t*)glfwGetWindowUserPointer(window);
			if (focus == GLFW_TRUE)
			{
				__window->m_Focus = true;
				GetEventQueue().emplace(event::window_focus_t{
					NEO_WINDOW_FOCUS_EVENT,
					__window,
					false
				});
			} else
			{
				__window->m_Focus = false;
				GetEventQueue().emplace(event::window_lost_focus_t{
					NEO_WINDOW_LOST_FOCUS_EVENT,
					__window,
					false
				});
			}

		});
		glfwSetCursorPosCallback(_window, [](GLFWwindow* window, double x, double y)
		{
			window_t* __window = (window_t*)glfwGetWindowUserPointer(window);
			GetEventQueue().emplace(event::mouse_moved_t{
				NEO_MOUSE_MOVED_EVENT,
				((window_t*)glfwGetWindowUserPointer(window)),
				false,
				(float)x, (float)y
			});
		});
		glfwSetScrollCallback(_window, [](GLFWwindow* window, double x_offset, double y_offset)
		{
			GetEventQueue().emplace(event::mouse_scrolled_t{
				NEO_MOUSE_SCROLLED_EVENT,
				((window_t*)glfwGetWindowUserPointer(window)),
				false,
				(float)x_offset, (float)y_offset
			});
		});
		glfwSetMouseButtonCallback(_window, [](GLFWwindow* window, int button, int action, int mods)
		{
			switch (action)
			{
			case GLFW_PRESS:
				GetEventQueue().emplace(event::mouse_button_pressed_t{
					NEO_MOUSE_BUTTON_PRESSED_EVENT,
					((window_t*)glfwGetWindowUserPointer(window)),
					false,
					(uint8_t)button
				});
				break;
			case GLFW_RELEASE:
				GetEventQueue().emplace(event::mouse_button_released_t{
					NEO_MOUSE_BUTTON_RELEASED_EVENT,
					((window_t*)glfwGetWindowUserPointer(window)),
					false,
					(uint8_t)button
				});
				break;
			}
		});
	}

} // namespace neo
