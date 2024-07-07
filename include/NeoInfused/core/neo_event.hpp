#if !defined(NEO_EVENT_HPP)
#define NEO_EVENT_HPP

#include "NeoInfused/neo_core.hpp"

// CODE COPIED FROM https://github.com/TheCherno/Hazel.git
namespace neo {
 	enum class EventType {
		None = 0,
		WindowClose, WindowResize, WindowFocus, WindowLostFocus,
		KeyPressed, KeyReleased, 
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled 
	};
#define EVENT_CLASS_TYPE(type) EventType type(void) { return EventType::##type; }

	class Event {
	public:
        Event(void) = default;
        virtual ~Event(void) = default;

		virtual EventType type(void) const = 0;
		virtual std::string str(void) const { return "Unknown Event"; }

		bool handled = false;
	};

    class KeyEvent : public Event {
	public:
		KeyEvent(int32_t _keycode) : m_Keycode(_keycode) {}
		inline int keycode(void) const { return m_Keycode; }
	protected:
		int32_t m_Keycode;
	};

	class KeyPressedEvent : public KeyEvent {
	public:
		KeyPressedEvent(int32_t _keycode, uint32_t _repeat_count)
		: KeyEvent(_keycode), m_RepeatCount(_repeat_count) {}
        inline EventType type(void) const override { return EventType::KeyPressed; }

		std::string str(void) const override { return NEO_FORMAT("KeyPressedEvent: {0}, {1}", m_Keycode, m_RepeatCount); }
        inline uint32_t repeat_count(void) const { return m_RepeatCount; }
	private:
		uint32_t m_RepeatCount;
	};

	class KeyReleasedEvent : public KeyEvent {
	public:
		KeyReleasedEvent(int32_t _keycode) : KeyEvent(_keycode) {}
        inline EventType type(void) const override { return EventType::KeyReleased; }

		std::string str(void) const override { return NEO_FORMAT("KeyReleasedEvent: {0}", m_Keycode); }
	};

    class WindowEvent : public Event {
    public:
        WindowEvent(uint16_t _window_id) : m_WindowId(_window_id) {}
        inline uint16_t window_id(void) const { return m_WindowId; }
    protected:
        uint16_t m_WindowId;
    };

    class WindowResizeEvent : public WindowEvent {
	public:
		WindowResizeEvent(uint32_t _width, uint32_t _height, uint16_t _window_id)
        : m_Width(_width), m_Height(_height), WindowEvent(_window_id) {}
        inline EventType type(void) const override { return EventType::WindowResize; }

		inline uint32_t width(void) const { return m_Width; }
		inline uint32_t height(void) const { return m_Height; }

		std::string str(void) const override { return NEO_FORMAT("WindowResizeEvent: {0}, {1}, window_id: {2}", m_Width, m_Height, m_WindowId); }
	private:
		uint32_t m_Width, m_Height;
	};

	class WindowCloseEvent : public WindowEvent {
	public:
		WindowCloseEvent(uint16_t _window_id) : WindowEvent(_window_id) {}
        inline EventType type(void) const override { return EventType::WindowClose; }
        inline std::string str(void) const override { return NEO_FORMAT("WindowCloseEvent: {0}", m_WindowId); }
	};

	class WindowFocusEvent : public WindowEvent {
	public:
		WindowFocusEvent(uint16_t _window_id) : WindowEvent(_window_id) {}
		inline EventType type(void) const override { return EventType::WindowFocus; }
		inline std::string str(void) const override { return NEO_FORMAT("WindowFocusEvent: {0}", m_WindowId); }
	};
	class WindowLostFocusEvent : public WindowEvent {
	public:
		WindowLostFocusEvent(uint16_t _window_id) : WindowEvent(_window_id) {}
		inline EventType type(void) const override { return EventType::WindowLostFocus; }
		inline std::string str(void) const override { return NEO_FORMAT("WindowLostFocusEvent: {0}", m_WindowId); }
	};


    class MouseMovedEvent : public Event {
	public:
		MouseMovedEvent(double _x, double _y) : m_X(_x), m_Y(_y) {}
		inline EventType type(void) const override { return EventType::MouseMoved; }

		inline double x(void) const { return m_X; }
		inline double y(void) const { return m_Y; }

		inline std::string str(void) const override { return NEO_FORMAT("MouseMovedEvent: {0}, {1}", m_X, m_Y); }
	private:
		double m_X, m_Y;
	};

	class MouseScrolledEvent : public Event {
	public:
		MouseScrolledEvent(double _x_offset, double _y_offset) : m_XOffset(_x_offset), m_YOffset(_y_offset) {}
		inline EventType type(void) const override { return EventType::MouseScrolled; }

		inline double x_offset(void) const { return m_XOffset;  }
		inline double y_offset(void) const { return m_YOffset;  }

		inline std::string str(void) const override { return NEO_FORMAT("MouseScrolledEvent: {0}, {1}", m_XOffset, m_YOffset); }
	private:
		double m_XOffset, m_YOffset;
	};

	class MouseButtonEvent : public Event {
	public:
		MouseButtonEvent(int32_t _button) : m_Button(_button) {}
		inline int32_t button(void) const { return m_Button; }
	protected:
		int32_t m_Button;
	};

	class MouseButtonPressedEvent : public MouseButtonEvent {
	public: 
		MouseButtonPressedEvent(int32_t _button) : MouseButtonEvent(_button) {}
        inline EventType type(void) const override { return EventType::MouseButtonPressed; }
		inline std::string str(void) const override { return NEO_FORMAT("MouseButtonPressedEvent: {0}", m_Button); }
	};

	class MouseButtonReleasedEvent : public MouseButtonEvent {
	public:
		MouseButtonReleasedEvent(int32_t _button) : MouseButtonEvent(_button) {}
        inline EventType type(void) const override { return EventType::MouseButtonReleased; }
		inline std::string str(void) const override { return NEO_FORMAT("MouseButtonReleasedEvent: {0}", m_Button); }
	};
} // namespace neo

#endif // NEO_EVENT_HPP