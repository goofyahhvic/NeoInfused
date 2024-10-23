#if !defined(NEO_INPUT_HPP)
#define NEO_INPUT_HPP

#include "NeoInfused/core/neo_input_macros.h"
#include "NeoInfused/core/neo_event.hpp"

namespace neo {
	class input_t {
	public:
		struct mouse_pos_t { float x = 0.0f, y = 0.0f; };

		input_t(void) { this->reset(); }
		~input_t(void) = default;

		void on_event(const event_t& e);
		inline void reset(void) { memset(this, 0, sizeof(input_t)); }

		[[nodiscard]] inline bool  key(uint16_t index) const { return m_Keys[index]; }
		[[nodiscard]] inline bool* keys(void) { return m_Keys; }

		[[nodiscard]] inline bool  mouse_button(uint8_t index) const { return m_MBs[index]; }
		[[nodiscard]] inline bool* mouse_buttons(void) { return m_MBs; }

		[[nodiscard]] inline float mouse_x(void) const { return m_MousePos.x; }
		[[nodiscard]] inline float mouse_y(void) const { return m_MousePos.y; }
		[[nodiscard]] inline mouse_pos_t& mouse_pos(void) { return m_MousePos; }
	private:
		bool m_Keys[NEO_KEY_LAST];
		bool m_MBs[NEO_MOUSE_BUTTON_LAST];
		mouse_pos_t m_MousePos;
	};
} // namespace neo

#endif // NEO_INPUT_HPP