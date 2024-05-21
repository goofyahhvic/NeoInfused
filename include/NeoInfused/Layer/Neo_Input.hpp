#if !defined(NEO_INPUT_HPP)
#define NEO_INPUT_HPP

#include <array>

namespace neo {
    class Input {
    public:
        using keys_array = std::array<bool, SDL_NUM_SCANCODES>;
        using mb_array = std::array<bool, SDL_BUTTON_X2>;
    public:
        Input(void) : m_Keys(), m_MouseButtons() {}
        ~Input(void) = default;
    public:
        inline bool& get_key(index_t index) { return m_Keys[index]; }
        inline const bool& get_key(index_t index) const { return m_Keys[index]; }
        inline keys_array& get_keys_array(void) { return m_Keys; }
        inline const keys_array& get_keys_array(void) const { return m_Keys; }

        inline bool& get_mb(index_t index) { return m_MouseButtons[index]; }
        inline const bool& get_mb(index_t index) const { return m_MouseButtons[index]; }
        inline mb_array& get_mb_array(void) { return m_MouseButtons; }
        inline const mb_array& get_mb_array(void) const { return m_MouseButtons; }

        inline void set_key(index_t index, bool value) { m_Keys[index] = value; }
        inline void set_mb(index_t index, bool value) { m_MouseButtons[index] = value; }

        inline void set_keys(bool value) { m_Keys.fill(value); }
        inline void set_mb(bool value) { m_MouseButtons.fill(value); }
        inline void reset(void) { m_Keys.fill(false); m_MouseButtons.fill(false); }
    private:
        keys_array m_Keys;
        mb_array m_MouseButtons;
    };
    using keys_array = Input::keys_array;
    using mb_array = Input::mb_array;
} // namespace neo

#endif // NEO_INPUT_HPP