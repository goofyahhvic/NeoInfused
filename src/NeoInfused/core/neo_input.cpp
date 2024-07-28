#include "neo_pch.hpp"
#include "NeoInfused/core/neo_input.hpp"

namespace neo {
    void Input::on_event(const Event& e) {
        switch (e.type) {
        case NEO_KEY_PRESSED_EVENT:
            m_Keys[((const KeyPressedEvent&)e).key] = true;
            break;
        case NEO_KEY_RELEASED_EVENT:
            m_Keys[((const KeyReleasedEvent&)e).key] = false;
            break;
        case NEO_MOUSE_BUTTON_PRESSED_EVENT:
            m_MBs[((const MouseButtonPressedEvent&)e).button] = true;
            break;
        case NEO_MOUSE_BUTTON_RELEASED_EVENT:
            m_MBs[((const MouseButtonReleasedEvent&)e).button] = false;
            break;
        case NEO_MOUSE_MOVED_EVENT:
            m_MousePos = { ((const MouseMovedEvent&)e).x, ((const MouseMovedEvent&)e).y };
            break;
        }
    }
} // namespace neo
