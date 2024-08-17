#include "neo_pch.hpp"
#include "NeoInfused/core/neo_window.hpp"

#include "NeoInfused/core/neo_app.hpp"
#include "NeoInfused/graphics/neo_context.hpp"

namespace neo {
	Window::Window(uint32_t id, uint32_t width, uint32_t height, const char* title)
		: m_Window(glfwCreateWindow(width, height, title, nullptr, nullptr)),
		m_Width(width), m_Height(height), m_Focus(true), m_Id(id)
	{
		NEO_ASSERT(m_Window, "Failed to create glfw window!");
		glfwSetWindowUserPointer(m_Window, (void*)this);

		if (!Context::Initialized())
			Context::Get().initialize(this);
		Context::Get().set_viewport(this, width, height);

		Window::_SetGLFWCallbacks(m_Window);
	}
	void Window::destroy(void)
	{
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
				GetEventHandler().push_event(KeyPressedEvent{
					NEO_KEY_PRESSED_EVENT,
					((Window*)glfwGetWindowUserPointer(window))->m_Id,
					false,
					(uint16_t)key,
					false
				});
				break;
			case GLFW_REPEAT:
				GetEventHandler().push_event(KeyPressedEvent{
					NEO_KEY_PRESSED_EVENT,
					((Window*)glfwGetWindowUserPointer(window))->m_Id,
					false,
					(uint16_t)key,
					true
				});
				break;
			case GLFW_RELEASE:
				GetEventHandler().push_event(KeyReleasedEvent{
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
			Context::Get().set_viewport(__window, width, height);
			GetEventHandler().push_event(WindowResizeEvent{
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
			GetEventHandler().push_event(WindowCloseEvent{
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
				GetEventHandler().push_event(WindowFocusEvent{
					NEO_WINDOW_FOCUS_EVENT,
					__window->m_Id,
					false
				});
			} else
			{
				__window->m_Focus = false;
				GetEventHandler().push_event(WindowLostFocusEvent{
					NEO_WINDOW_LOST_FOCUS_EVENT,
					__window->m_Id,
					false
				});
			}

		});
		glfwSetCursorPosCallback(_window, [](GLFWwindow* window, double x, double y)
		{
			Window* __window = (Window*)glfwGetWindowUserPointer(window);
			GetEventHandler().push_event(MouseMovedEvent{
				NEO_MOUSE_MOVED_EVENT,
				((Window*)glfwGetWindowUserPointer(window))->m_Id,
				false,
				(float)x, (float)y
			});
		});
		glfwSetScrollCallback(_window, [](GLFWwindow* window, double x_offset, double y_offset)
		{
			GetEventHandler().push_event(MouseScrolledEvent{
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
				GetEventHandler().push_event(MouseButtonPressedEvent{
					NEO_MOUSE_BUTTON_PRESSED_EVENT,
					((Window*)glfwGetWindowUserPointer(window))->m_Id,
					false,
					(uint8_t)button
				});
				break;
			case GLFW_RELEASE:
				GetEventHandler().push_event(MouseButtonReleasedEvent{
					NEO_MOUSE_BUTTON_RELEASED_EVENT,
					((Window*)glfwGetWindowUserPointer(window))->m_Id,
					false,
					(uint8_t)button
				});
				break;
			}
		});
	}

	void Window::_GLFWPollEvents(void)
	{ glfwPollEvents(); }

} // namespace neo
