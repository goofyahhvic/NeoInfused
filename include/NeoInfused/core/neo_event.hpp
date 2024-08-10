#if !defined(NEO_EVENT_HPP)
#define NEO_EVENT_HPP

#include "NeoInfused/neo_core.hpp"

enum neo_EventType {
	NEO_EVENT_NONE = 0,
	NEO_KEY_PRESSED_EVENT, NEO_KEY_RELEASED_EVENT,
	NEO_WINDOW_RESIZE_EVENT, NEO_WINDOW_CLOSE_EVENT, NEO_WINDOW_FOCUS_EVENT, NEO_WINDOW_LOST_FOCUS_EVENT,
	NEO_MOUSE_MOVED_EVENT, NEO_MOUSE_SCROLLED_EVENT, NEO_MOUSE_BUTTON_PRESSED_EVENT, NEO_MOUSE_BUTTON_RELEASED_EVENT
};
#define NEO_EVENT_BASE(x) struct {\
						uint8_t type = x;\
						uint32_t window_id;\
						bool handled = false;\
					 }

namespace neo {
	using EventType = neo_EventType;
	struct Event {
		NEO_EVENT_BASE(NEO_EVENT_NONE);
		uint32_t padding1 = 0, padding2 = 0;
	};

	struct KeyPressedEvent {
		NEO_EVENT_BASE(NEO_KEY_PRESSED_EVENT);
		uint16_t key;
		bool repeat;
		uint32_t padding = 0;
	};

	struct KeyReleasedEvent {
		NEO_EVENT_BASE(NEO_KEY_RELEASED_EVENT);
		uint16_t key;
		uint32_t padding = 0;
	};

	struct WindowResizeEvent {
		NEO_EVENT_BASE(NEO_WINDOW_RESIZE_EVENT);
		uint32_t width, height;
	};

	struct WindowCloseEvent {
		NEO_EVENT_BASE(NEO_WINDOW_CLOSE_EVENT);
		uint32_t padding1 = 0, padding2 = 0;
	};

	struct WindowFocusEvent {
		NEO_EVENT_BASE(NEO_WINDOW_FOCUS_EVENT);
		uint32_t padding1 = 0, padding2 = 0;
	};
	struct WindowLostFocusEvent {
		NEO_EVENT_BASE(NEO_WINDOW_LOST_FOCUS_EVENT);
		uint32_t padding1 = 0, padding2 = 0;
	};

	struct MouseMovedEvent {
		NEO_EVENT_BASE(NEO_MOUSE_MOVED_EVENT);
		float x, y;
	};

	struct MouseScrolledEvent {
		NEO_EVENT_BASE(NEO_MOUSE_SCROLLED_EVENT);
		float x_offset, y_offset;
	};

	struct MouseButtonPressedEvent {
		NEO_EVENT_BASE(NEO_MOUSE_BUTTON_PRESSED_EVENT);
		uint8_t button;
		uint32_t padding = 0;
	};

	struct MouseButtonReleasedEvent {
		NEO_EVENT_BASE(NEO_MOUSE_BUTTON_RELEASED_EVENT);
		uint8_t button;
		uint32_t padding = 0;
	};
} // namespace neo

#endif // NEO_EVENT_HPP