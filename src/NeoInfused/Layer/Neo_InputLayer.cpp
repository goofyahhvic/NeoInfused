#include "Neo_PCH.hpp"
#include "NeoInfused/Layer/Neo_InputLayer.hpp"

#define NEO_KEYBOARD_EVENT ((SDL_KeyboardEvent*)e)
#define NEO_MOUSEBUTTON_EVENT ((SDL_MouseButtonEvent*)e)

namespace neo {
#if !defined(NEO_CONFIG_DIST)
    InputLayer::InputLayer(const std::string& debug_name, bool enabled) : Layer(debug_name, enabled) {
#else
    InputLayer::InputLayer(bool enabled) : Layer(enabled) {
#endif // NEO_CONFIG_DIST
        this->input = Input();
    }
    bool InputLayer::handle_event(SDL_Event* e) {
        this->set_input(e);
        return true;
    }
    void InputLayer::set_input(SDL_Event* e) {
        switch (e->type) {
        case SDL_KEYDOWN:
            this->input.get_key(NEO_KEYBOARD_EVENT->keysym.scancode) = true;
            break;
        case SDL_KEYUP:
            this->input.get_key(NEO_KEYBOARD_EVENT->keysym.scancode) = false;
            break;
        case SDL_MOUSEBUTTONDOWN:
            this->input.get_mb(NEO_MOUSEBUTTON_EVENT->button) = true;
            break;
        case SDL_MOUSEBUTTONUP:
            this->input.get_mb(NEO_MOUSEBUTTON_EVENT->button) = false;
            break;
        }
    }
} // namespace neo
