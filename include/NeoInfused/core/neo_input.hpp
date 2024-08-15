#if !defined(NEO_INPUT_HPP)
#define NEO_INPUT_HPP

#include "NeoInfused/core/neo_input_macros.h"
#include "NeoInfused/core/neo_event.hpp"

#define C_INPUT (const neo::Input*)(&m_Input)

namespace neo {
	class Input {
	public:
		using Keys = std::array<bool, NEO_KEY_LAST>;
		using MouseButtons = std::array<bool, NEO_MOUSE_BUTTON_LAST>;
		struct MousePos { float x = 0.0f, y = 0.0f; };

		Input(void) = default;
		~Input(void) = default;

		void on_event(const Event& e);

		[[nodiscard]] inline bool& key(uint16_t index) { return m_Keys[index]; }
		[[nodiscard]] inline bool  key(uint16_t index) const { return m_Keys[index]; }

		[[nodiscard]] inline Keys& keys(void) { return m_Keys; }
		[[nodiscard]] inline const Keys& keys(void) const { return m_Keys; }

		[[nodiscard]] inline bool& mouse_button(uint8_t index) { return m_MBs[index]; }
		[[nodiscard]] inline bool  mouse_button(uint8_t index) const { return m_MBs[index]; }

		[[nodiscard]] inline MouseButtons& mouse_buttons(void) { return m_MBs; }
		[[nodiscard]] inline const MouseButtons& mouse_buttons(void) const { return m_MBs; }

		[[nodiscard]] inline float& mouse_x(void) { return m_MousePos.x; }
		[[nodiscard]] inline float  mouse_x(void) const { return m_MousePos.x; }

		[[nodiscard]] inline float& mouse_y(void) { return m_MousePos.y; }
		[[nodiscard]] inline float  mouse_y(void) const { return m_MousePos.y; }

		[[nodiscard]] inline MousePos& mouse_pos(void) { return m_MousePos; }
		[[nodiscard]] inline const MousePos& mouse_pos(void) const { return m_MousePos; }

		inline void reset(void) { m_Keys.fill(false); m_MBs.fill(false); m_MousePos = (MousePos)0llu; }
	private:
		Keys m_Keys;
		MouseButtons m_MBs;
		MousePos m_MousePos;
	};
} // namespace neo

#endif // NEO_INPUT_HPP