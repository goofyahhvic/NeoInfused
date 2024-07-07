#include "neo_pch.hpp"
#include "NeoInfused/core/neo_window.hpp"

#include "NeoInfused/graphics/neo_context.hpp"

namespace neo {
    uint16_t Window::m_LastId = 0;
    std::unordered_map<uint16_t, Window*> Window::m_Windows;

    Window::Window(int32_t width, int32_t height, const char* title) {
        m_Window = glfwCreateWindow(width, height, title, nullptr, nullptr);
        glfwSetWindowUserPointer(m_Window, this);
        SetGLFWCallbacks(m_Window);

        m_Id = m_LastId++;
        Window::m_Windows[m_Id] = this;

        if (!Context::Initialized())
			Context::Get()->initialize(this);
		Context::Get()->set_viewport(this, width, height);
    }
    Window::~Window(void) {
        Window::m_Windows.erase(m_Id);
        glfwDestroyWindow(m_Window);
    }

    void Window::SetGLFWCallbacks(GLFWwindow* _window) {
        glfwSetWindowSizeCallback(_window, [] (GLFWwindow* window, int width, int height) {
			Window* __window = (Window*)glfwGetWindowUserPointer(window);
			__window->m_Width = width;
			__window->m_Height = height;
            WindowResizeEvent e(width, height, __window->m_Id);
			__window->on_event(&e);
		});
		glfwSetWindowCloseCallback(_window, [] (GLFWwindow* window) {
			Window* __window = (Window*)glfwGetWindowUserPointer(window);
            __window->should_close = true;
            WindowCloseEvent e(__window->m_Id);
			__window->on_event(&e);
		});
		glfwSetWindowFocusCallback(_window, [](GLFWwindow* window, int focus){
			Window* __window = (Window*)glfwGetWindowUserPointer(window);
			if (focus == GLFW_TRUE) {
				WindowFocusEvent e(__window->m_Id);
				__window->on_event(&e);
			} else {
				WindowLostFocusEvent e(__window->m_Id);
				__window->on_event(&e);
			}
		});
		glfwSetKeyCallback(_window, [] (GLFWwindow* window, int key, int scancode, int action, int mods) {
			Window* __window = (Window*)glfwGetWindowUserPointer(window);
			switch (action) {
				case GLFW_PRESS: {
                    KeyPressedEvent e(key, 0);
					__window->on_event(&e);
					break;
				}
				case GLFW_RELEASE: {
                    KeyReleasedEvent e(key);
					__window->on_event(&e);
					break;
				}
				case GLFW_REPEAT: {
                    KeyPressedEvent e(key, 1);
					__window->on_event(&e);
					break;
				}
			}
		});
		glfwSetMouseButtonCallback(_window, [] (GLFWwindow* window, int button, int action, int mods) {
			Window* __window = (Window*)glfwGetWindowUserPointer(window);
			switch (action) {
				case GLFW_PRESS: {
                    MouseButtonPressedEvent e(button);
					__window->on_event(&e);
					break;
				}
				case GLFW_RELEASE: {
                    MouseButtonReleasedEvent e(button);
					__window->on_event(&e);
					break;
				}
			}
		});
		glfwSetScrollCallback(_window, [] (GLFWwindow* window, double x_offset, double y_offset) {
			Window* __window = (Window*)glfwGetWindowUserPointer(window);
            MouseScrolledEvent e(x_offset, y_offset);
			__window->on_event(&e);
		});
		glfwSetCursorPosCallback(_window, [] (GLFWwindow* window, double x, double y) {
			Window* __window = (Window*)glfwGetWindowUserPointer(window);
            MouseMovedEvent e(x, y);
			__window->on_event(&e);
		});
    }

	void PollEvents(void) {
		glfwPollEvents();
	}
} // namespace neo
