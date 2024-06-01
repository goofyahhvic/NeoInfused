#include "Neo_PCH.hpp"
#include "NeoInfused/Layer/Neo_InputLayer.hpp"

#define NEO_KEYBOARD_EVENT ((SDL_KeyboardEvent*)e)
#define NEO_MOUSEBUTTON_EVENT ((SDL_MouseButtonEvent*)e)
#define NEO_MOUSEMOTION_EVENT ((SDL_MouseMotionEvent*)e)

namespace neo {
    InputLayer::InputLayer(float priority) : Layer(priority) {
        m_Input = Input();
    }
    bool InputLayer::handle_event(SDL_Event* e) {
        this->_set_input(e);
        return true;
    }
    void InputLayer::_set_input(SDL_Event* e) {   
        switch (e->type) {
        case SDL_KEYDOWN:
            m_Input.get_key(NEO_KEYBOARD_EVENT->keysym.scancode) = true;
            break;
        case SDL_KEYUP:
            m_Input.get_key(NEO_KEYBOARD_EVENT->keysym.scancode) = false;
            break;
        case SDL_MOUSEBUTTONDOWN:
            m_Input.get_mb(NEO_MOUSEBUTTON_EVENT->button) = true;
            break;
        case SDL_MOUSEBUTTONUP:
            m_Input.get_mb(NEO_MOUSEBUTTON_EVENT->button) = false;
            break;
        case SDL_MOUSEMOTION:
            m_Input.set_mp(NEO_MOUSEMOTION_EVENT->x, NEO_MOUSEMOTION_EVENT->y);
            break;
        }
    }
} // namespace neo
