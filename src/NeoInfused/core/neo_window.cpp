#include "neo_pch.hpp"
#include "NeoInfused/core/neo_window.hpp"

#include "NeoInfused/core/neo_app.hpp"
#include "NeoInfused/graphics/neo_context.hpp"

#define E(x) x,\
							__window->m_Id,\
							false
#define PUSH_EVENT App::Get()->event_handler.push_event

namespace neo {
    Window::Window(uint32_t id, uint32_t width, uint32_t height, const std::string& title)
	: m_Window(glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr)),
	m_Width(width), m_Height(height), m_Focus(true), m_Id(id) {
		NEO_ASSERT(m_Window, "Failed to create glfw window!");
		glfwSetWindowUserPointer(m_Window, (void*)this);

        if (!Context::Initialized())
			Context::Get()->initialize(this);
		Context::Get()->set_viewport(this, width, height);

		Window::_SetGLFWCallbacks(m_Window);
    }
	Window::Window(Window&& other) noexcept
	: m_Window(std::move(other.m_Window)),
	m_Width(std::exchange(other.m_Width, 0)), m_Height(std::exchange(other.m_Height, 0)),
	m_Focus(std::exchange(other.m_Focus, false)) {

	}
	Window::~Window(void) {
		glfwDestroyWindow(m_Window);
	}

	void Window::set_size(uint32_t width, uint32_t height) {
		glfwSetWindowSize(m_Window, width, height);
		m_Width = width;
		m_Height = height;
	}
	void Window::set_title(const char* title) {
		glfwSetWindowTitle(m_Window, title);
	}
	const char* Window::title(void) const {
		return glfwGetWindowTitle(m_Window);
	}

    void Window::_SetGLFWCallbacks(GLFWwindow* _window) {
		glfwSetKeyCallback(_window, [] (GLFWwindow* window, int key, int scancode, int action, int mods) {
			Window* __window = (Window*)glfwGetWindowUserPointer(window);
			switch (action) {
				case GLFW_PRESS:
					PUSH_EVENT(KeyPressedEvent {
						E(NEO_KEY_PRESSED_EVENT),
						(uint16_t)key,
						false
					});
					break;
				case GLFW_RELEASE:
					PUSH_EVENT(KeyReleasedEvent {
						E(NEO_KEY_RELEASED_EVENT),
						(uint16_t)key
					});
					break;
				case GLFW_REPEAT:
					PUSH_EVENT(KeyPressedEvent {
						E(NEO_KEY_PRESSED_EVENT),
						(uint16_t)key,
						true
					});
					break;
			}
		});
        glfwSetWindowSizeCallback(_window, [] (GLFWwindow* window, int width, int height) {
			Window* __window = (Window*)glfwGetWindowUserPointer(window);
			__window->m_Width = width;
			__window->m_Height = height;
			PUSH_EVENT(WindowResizeEvent {
				E(NEO_WINDOW_RESIZE_EVENT),
				(uint32_t)width, (uint32_t)height
			});
		});
		glfwSetWindowCloseCallback(_window, [] (GLFWwindow* window) {
			Window* __window = (Window*)glfwGetWindowUserPointer(window);
			__window->should_close = true;
			PUSH_EVENT(WindowCloseEvent {
				E(NEO_WINDOW_CLOSE_EVENT)
			});
		});
		glfwSetWindowFocusCallback(_window, [](GLFWwindow* window, int focus) {
			Window* __window = (Window*)glfwGetWindowUserPointer(window);
			if (focus == GLFW_TRUE) {
				__window->m_Focus = true;
				PUSH_EVENT(WindowFocusEvent {
					E(NEO_WINDOW_FOCUS_EVENT)
				});
			} else {
				__window->m_Focus = false;
				PUSH_EVENT(WindowLostFocusEvent {
					E(NEO_WINDOW_LOST_FOCUS_EVENT)
				});
			}
			
		});
		glfwSetCursorPosCallback(_window, [] (GLFWwindow* window, double x, double y) {
			Window* __window = (Window*)glfwGetWindowUserPointer(window);
			PUSH_EVENT(MouseMovedEvent {
				E(NEO_MOUSE_MOVED_EVENT),
				(float)x, (float)y
			});
		});
		glfwSetScrollCallback(_window, [] (GLFWwindow* window, double x_offset, double y_offset) {
			Window* __window = (Window*)glfwGetWindowUserPointer(window);
			PUSH_EVENT(MouseScrolledEvent {
				E(NEO_MOUSE_SCROLLED_EVENT),
				(float)x_offset, (float)y_offset
			});
		});
		glfwSetMouseButtonCallback(_window, [] (GLFWwindow* window, int button, int action, int mods) {
			Window* __window = (Window*)glfwGetWindowUserPointer(window);
			switch (action) {
				case GLFW_PRESS:
					PUSH_EVENT(MouseButtonPressedEvent {
						E(NEO_MOUSE_BUTTON_PRESSED_EVENT),
						(uint8_t)button
					});
					break;
				case GLFW_RELEASE:
					PUSH_EVENT(MouseButtonReleasedEvent {
						E(NEO_MOUSE_BUTTON_RELEASED_EVENT),
						(uint8_t)button
					});
					break;
			}
		});
    }

	void Window::_GLFWPollEvents(void) {
		glfwPollEvents();
	}
} // namespace neo
