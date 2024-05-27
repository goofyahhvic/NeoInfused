#if !defined(NEO_INPUT_HPP)
#define NEO_INPUT_HPP

namespace neo {
    class Input {
    public:
        using keys_array = std::array<bool, SDL_NUM_SCANCODES>;
        using mb_array = std::array<bool, SDL_BUTTON_X2>;
        struct MousePos { int32_t x = 0, y = 0; };
    public:
        Input(void) : m_Keys(), m_MouseButtons() {}
        ~Input(void) = default;
    public:
        inline bool& get_key(index16_t index) { return m_Keys[index]; }
        inline const bool& get_key(index16_t index) const { return m_Keys[index]; }

        inline keys_array& get_keys_array(void) { return m_Keys; }
        inline const keys_array& get_keys_array(void) const { return m_Keys; }

        inline bool& get_mb(index8_t index) { return m_MouseButtons[index]; }
        inline const bool& get_mb(index8_t index) const { return m_MouseButtons[index]; }

        inline mb_array& get_mb_array(void) { return m_MouseButtons; }
        inline const mb_array& get_mb_array(void) const { return m_MouseButtons; }

        inline MousePos& get_mp(void) { return m_MousePos; }
        inline const MousePos& get_mp(void) const { return m_MousePos; }

        int32_t get_mouse_x(void) const { return m_MousePos.x; }
        int32_t& get_mouse_x(void) { return m_MousePos.x; }

        int32_t get_mouse_y(void) const { return m_MousePos.y; }
        int32_t& get_mouse_y(void) { return m_MousePos.y; }

        inline void set_key(index16_t index, bool value) { m_Keys[index] = value; }
        inline void set_mb(index8_t index, bool value) { m_MouseButtons[index] = value; }
        inline void set_mp(int32_t x, int32_t y) { m_MousePos.x = x; m_MousePos.y = y; }

        inline void set_keys(bool value) { m_Keys.fill(value); }
        inline void set_mb(bool value) { m_MouseButtons.fill(value); }
        inline void reset(void) { m_Keys.fill(false); m_MouseButtons.fill(false); }
    private:
        keys_array m_Keys;
        mb_array m_MouseButtons;
        MousePos m_MousePos;
    };
    using keys_array = Input::keys_array;
    using mb_array = Input::mb_array;
    using MousePos = Input::MousePos;
} // namespace neo

#endif // NEO_INPUT_HPP