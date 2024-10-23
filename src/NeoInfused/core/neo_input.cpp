#include "neo_pch.hpp"
#include "NeoInfused/core/neo_input.hpp"

namespace neo {
	void input_t::on_event(const event_t& e)
	{
		switch (e.type)
		{
		case NEO_KEY_PRESSED_EVENT:
			m_Keys[((const event::key_pressed_t&)e).key] = true;
			break;
		case NEO_KEY_RELEASED_EVENT:
			m_Keys[((const event::key_released_t&)e).key] = false;
			break;
		case NEO_MOUSE_BUTTON_PRESSED_EVENT:
			m_MBs[((const event::mouse_button_pressed_t&)e).button] = true;
			break;
		case NEO_MOUSE_BUTTON_RELEASED_EVENT:
			m_MBs[((const event::mouse_button_released_t&)e).button] = false;
			break;
		case NEO_MOUSE_MOVED_EVENT:
			m_MousePos.x = ((const event::mouse_moved_t&)e).x;
			m_MousePos.y = ((const event::mouse_moved_t&)e).y;
			break;
		}
	}

} // namespace neo
