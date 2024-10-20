#include "neo_pch.hpp"
#include "NeoInfused/core/neo_window.hpp"

#include "NeoInfused/core/neo_app.hpp"
#include "influx/inf_loader.hpp"

namespace neo {
	Window::Window(uint32_t id, uint32_t width, uint32_t height, const char* title)
		: m_Window(glfwCreateWindow(width, height, title, nullptr, nullptr)),
		m_Width(width), m_Height(height), m_Id(id),
		surface(m_Window)
	{
		NEO_ASSERT(m_Window, "Failed to create glfw window!");
		NEO_ASSERT(surface, "Failed to create window surface!");
		glfwSetWindowUserPointer(m_Window, this);

		Window::_SetGLFWCallbacks(m_Window);
	}
	void Window::destroy(void)
	{
		surface.destroy();
		glfwDestroyWindow(m_Window);
		m_Window = nullptr;
	}

	void Window::focus(void)
	{
		glfwFocusWindow(m_Window);
	}

	void Window::set_size(uint32_t width, uint32_t height)
	{
		glfwSetWindowSize(m_Window, width, height);
		m_Width = width;
		m_Height = height;
	}
	void Window::set_title(const char* title)
	{
		glfwSetWindowTitle(m_Window, title);
	}

	const char* Window::title(void) const
	{
		return glfwGetWindowTitle(m_Window);
	}

	void Window::_SetGLFWCallbacks(GLFWwindow* _window)
	{
		glfwSetKeyCallback(_window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			switch (action)
			{
			case GLFW_PRESS:
				GetEventQueue().emplace(KeyPressedEvent{
					NEO_KEY_PRESSED_EVENT,
					((Window*)glfwGetWindowUserPointer(window))->m_Id,
					false,
					(uint16_t)key,
					false
				});
				break;
			case GLFW_REPEAT:
				GetEventQueue().emplace(KeyPressedEvent{
					NEO_KEY_PRESSED_EVENT,
					((Window*)glfwGetWindowUserPointer(window))->m_Id,
					false,
					(uint16_t)key,
					true
				});
				break;
			case GLFW_RELEASE:
				GetEventQueue().emplace(KeyReleasedEvent{
					NEO_KEY_RELEASED_EVENT,
					((Window*)glfwGetWindowUserPointer(window))->m_Id,
					false,
					(uint16_t)key
				});
				break;
			}
		});
		glfwSetWindowSizeCallback(_window, [](GLFWwindow* window, int width, int height)
		{
			Window* __window = (Window*)glfwGetWindowUserPointer(window);
			__window->m_Width = width;
			__window->m_Height = height;
			GetEventQueue().emplace(WindowResizeEvent{
				NEO_WINDOW_RESIZE_EVENT,
				__window->m_Id,
				false,
				(uint32_t)width, (uint32_t)height
			});
		});
		glfwSetWindowCloseCallback(_window, [](GLFWwindow* window)
		{
			Window* __window = (Window*)glfwGetWindowUserPointer(window);
			__window->should_close = true;
			GetEventQueue().emplace(WindowCloseEvent{
				NEO_WINDOW_CLOSE_EVENT,
				__window->m_Id,
				false
			});
		});
		glfwSetWindowFocusCallback(_window, [](GLFWwindow* window, int focus)
		{
			Window* __window = (Window*)glfwGetWindowUserPointer(window);
			if (focus == GLFW_TRUE)
			{
				__window->m_Focus = true;
				GetEventQueue().emplace(WindowFocusEvent{
					NEO_WINDOW_FOCUS_EVENT,
					__window->m_Id,
					false
				});
			} else
			{
				__window->m_Focus = false;
				GetEventQueue().emplace(WindowLostFocusEvent{
					NEO_WINDOW_LOST_FOCUS_EVENT,
					__window->m_Id,
					false
				});
			}

		});
		glfwSetCursorPosCallback(_window, [](GLFWwindow* window, double x, double y)
		{
			Window* __window = (Window*)glfwGetWindowUserPointer(window);
			GetEventQueue().emplace(MouseMovedEvent{
				NEO_MOUSE_MOVED_EVENT,
				((Window*)glfwGetWindowUserPointer(window))->m_Id,
				false,
				(float)x, (float)y
			});
		});
		glfwSetScrollCallback(_window, [](GLFWwindow* window, double x_offset, double y_offset)
		{
			GetEventQueue().emplace(MouseScrolledEvent{
				NEO_MOUSE_SCROLLED_EVENT,
				((Window*)glfwGetWindowUserPointer(window))->m_Id,
				false,
				(float)x_offset, (float)y_offset
			});
		});
		glfwSetMouseButtonCallback(_window, [](GLFWwindow* window, int button, int action, int mods)
		{
			switch (action)
			{
			case GLFW_PRESS:
				GetEventQueue().emplace(MouseButtonPressedEvent{
					NEO_MOUSE_BUTTON_PRESSED_EVENT,
					((Window*)glfwGetWindowUserPointer(window))->m_Id,
					false,
					(uint8_t)button
				});
				break;
			case GLFW_RELEASE:
				GetEventQueue().emplace(MouseButtonReleasedEvent{
					NEO_MOUSE_BUTTON_RELEASED_EVENT,
					((Window*)glfwGetWindowUserPointer(window))->m_Id,
					false,
					(uint8_t)button
				});
				break;
			}
		});
	}

} // namespace neo
