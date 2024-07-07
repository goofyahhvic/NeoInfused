#include "neo_pch.hpp"
#include "NeoInfused/core/neo_input.hpp"

namespace neo {
    void Input::on_event(const Event* e) {
        switch (e->type()) {
        case EventType::KeyPressed:
            m_Keys[((const KeyPressedEvent*)e)->keycode()] = true;
            break;
        case EventType::KeyReleased:
            m_Keys[((const KeyReleasedEvent*)e)->keycode()] = false;
            break;
        case EventType::MouseButtonPressed:
            m_MBs[((const MouseButtonPressedEvent*)e)->button()] = true;
            break;
        case EventType::MouseButtonReleased:
            m_MBs[((const MouseButtonReleasedEvent*)e)->button()] = false;
            break;
        case EventType::MouseMoved:
            m_MousePos = { ((const MouseMovedEvent*)e)->x(), ((const MouseMovedEvent*)e)->y() };
            break;
        default:
            break;
        }
    }
} // namespace neo
