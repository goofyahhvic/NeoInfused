#if !defined(NEO_EVENT_HPP)
#define NEO_EVENT_HPP

#include "NeoInfused/neo_core.hpp"
#include "NeoInfused/template/neo_array-list.hpp"

enum neo_event_type_t : uint8_t {
	NEO_EVENT_NONE = 0,
	NEO_KEY_PRESSED_EVENT, NEO_KEY_RELEASED_EVENT,
	NEO_WINDOW_RESIZE_EVENT, NEO_WINDOW_CLOSE_EVENT, NEO_WINDOW_FOCUS_EVENT, NEO_WINDOW_LOST_FOCUS_EVENT,
	NEO_MOUSE_MOVED_EVENT, NEO_MOUSE_SCROLLED_EVENT, NEO_MOUSE_BUTTON_PRESSED_EVENT, NEO_MOUSE_BUTTON_RELEASED_EVENT
};
#define NEO_EVENT_BASE(x) struct {\
						uint8_t type = x;\
						window_t* window;\
						bool handled = false;\
					 }

namespace neo {
	namespace window { class window_t; }
	using window_t = window::window_t;
	namespace event {
		using type_t = neo_event_type_t;

		struct key_pressed_t {
			NEO_EVENT_BASE(NEO_KEY_PRESSED_EVENT);
			uint16_t key;
			bool repeat;
			uint32_t padding = 0;
		};

		struct key_released_t {
			NEO_EVENT_BASE(NEO_KEY_RELEASED_EVENT);
			uint16_t key;
			uint32_t padding = 0;
		};

		struct window_resize_t {
			NEO_EVENT_BASE(NEO_WINDOW_RESIZE_EVENT);
			uint32_t width, height;
		};

		struct window_close_t {
			NEO_EVENT_BASE(NEO_WINDOW_CLOSE_EVENT);
			uint32_t padding1 = 0, padding2 = 0;
		};

		struct window_focus_t {
			NEO_EVENT_BASE(NEO_WINDOW_FOCUS_EVENT);
			uint32_t padding1 = 0, padding2 = 0;
		};
		struct window_lost_focus_t {
			NEO_EVENT_BASE(NEO_WINDOW_LOST_FOCUS_EVENT);
			uint32_t padding1 = 0, padding2 = 0;
		};

		struct mouse_moved_t {
			NEO_EVENT_BASE(NEO_MOUSE_MOVED_EVENT);
			float x, y;
		};

		struct mouse_scrolled_t {
			NEO_EVENT_BASE(NEO_MOUSE_SCROLLED_EVENT);
			float x_offset, y_offset;
		};

		struct mouse_button_pressed_t {
			NEO_EVENT_BASE(NEO_MOUSE_BUTTON_PRESSED_EVENT);
			uint8_t button;
			uint32_t padding = 0;
		};

		struct mouse_button_released_t {
			NEO_EVENT_BASE(NEO_MOUSE_BUTTON_RELEASED_EVENT);
			uint8_t button;
			uint32_t padding = 0;
		};

		struct event_t {
			uint8_t type;
			window_t* window;
			bool handled;
			uint32_t padding1, padding2;
			inline event_t(key_pressed_t&& e) { memcpy(this, &e, sizeof(event_t)); }
			inline event_t(key_released_t&& e) { memcpy(this, &e, sizeof(event_t)); }
			inline event_t(window_resize_t&& e) { memcpy(this, &e, sizeof(event_t)); }
			inline event_t(window_close_t&& e) { memcpy(this, &e, sizeof(event_t)); }
			inline event_t(window_focus_t&& e) { memcpy(this, &e, sizeof(event_t)); }
			inline event_t(window_lost_focus_t&& e) { memcpy(this, &e, sizeof(event_t)); }
			inline event_t(mouse_moved_t&& e) { memcpy(this, &e, sizeof(event_t)); }
			inline event_t(mouse_scrolled_t&& e) { memcpy(this, &e, sizeof(event_t)); }
			inline event_t(mouse_button_pressed_t&& e) { memcpy(this, &e, sizeof(event_t)); }
			inline event_t(mouse_button_released_t&& e) { memcpy(this, &e, sizeof(event_t)); }
		};

		using queue_t = array_list_t<event_t>;
		queue_t& poll(queue_t& queue);
	} // namespace event
	using event_t = event::event_t;
} // namespace neo

#endif // NEO_EVENT_HPP