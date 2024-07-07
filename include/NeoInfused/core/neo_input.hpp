#if !defined(NEO_INPUT_HPP)
#define NEO_INPUT_HPP

#include "NeoInfused/core/neo_input_macros.h"
#include "NeoInfused/core/neo_event.hpp"

namespace neo {
    class Input {
    public:
        using Keys = std::array<bool, NEO_KEY_LAST>;
        using MouseButtons = std::array<bool, NEO_MOUSE_BUTTON_LAST>;
        struct MousePos { double x = 0, y = 0; };
    public:
        Input(void) = default;
        ~Input(void) = default;
    public:
        void on_event(const Event* e);

        inline bool key(uint16_t index) const { return m_Keys[index]; }
        inline void set_key(uint16_t index, bool value) { m_Keys[index] = value; }
        inline Keys& keys(void) { return m_Keys; }
        inline const Keys& keys(void) const { return m_Keys; }

        inline bool mouse_button(uint8_t index) const { return m_MBs[index]; }
        inline void set_mouse_button(uint8_t index, bool value) { m_MBs[index] = value; }
        inline MouseButtons& mouse_buttons(void) { return m_MBs; }
        inline const MouseButtons& mouse_buttons(void) const { return m_MBs; }

        inline double mouse_x(void) const { return m_MousePos.x; }
        inline double mouse_y(void) const { return m_MousePos.y; }
        inline void set_mouse_x(double _x) { m_MousePos.x = _x; }
        inline void set_mouse_y(double _y) { m_MousePos.y = _y; }

        inline MousePos& mouse_pos(void) { return m_MousePos; }
        inline const MousePos& mouse_pos(void) const { return m_MousePos; }
        inline void set_mouse_pos(const MousePos& _pos) { m_MousePos = _pos; }

        inline void reset(void) { m_Keys.fill(false); m_MBs.fill(false); m_MousePos = {0.0f, 0.0f}; }
    private:
        Keys m_Keys;
        MouseButtons m_MBs;
        MousePos m_MousePos;
    };
} // namespace neo

#endif // NEO_INPUT_HPP