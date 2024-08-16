#if !defined(NEO_INPUT_HPP)
#define NEO_INPUT_HPP

#include "NeoInfused/core/neo_input_macros.h"
#include "NeoInfused/core/neo_event.hpp"

namespace neo {
	class Input {
	public:
		struct MousePos { float x = 0.0f, y = 0.0f; };

		Input(void) = default;
		~Input(void) = default;

		void on_event(const Event& e);
		void reset(void);

		[[nodiscard]] inline bool  key(uint16_t index) const { return m_Keys[index]; }
		[[nodiscard]] inline bool* keys(void) { return m_Keys; }

		[[nodiscard]] inline bool  mouse_button(uint8_t index) const { return m_MBs[index]; }
		[[nodiscard]] inline bool* mouse_buttons(void) { return m_MBs; }

		[[nodiscard]] inline float mouse_x(void) const { return m_MousePos.x; }
		[[nodiscard]] inline float mouse_y(void) const { return m_MousePos.y; }
		[[nodiscard]] inline MousePos& mouse_pos(void) { return m_MousePos; }
	private:
		bool m_Keys[NEO_KEY_LAST];
		bool m_MBs[NEO_MOUSE_BUTTON_LAST];
		MousePos m_MousePos;
	};
} // namespace neo

#endif // NEO_INPUT_HPP