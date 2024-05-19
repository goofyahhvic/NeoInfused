#if !defined(NEO_INPUT_HPP)
#define NEO_INPUT_HPP

#include <array>

namespace neo {
    class Input {
    public:
        using keys_array = std::array<bool, SDL_NUM_SCANCODES>;
        using mb_array = std::array<bool, SDL_BUTTON_X2>;
    public:
        Input(void) : keys(), mouse_buttons() {}
        ~Input(void) = default;
    public:
        inline bool& get_key(index_t index) { return Input::keys[index]; }
        inline const bool& get_key(index_t index) const { return Input::keys[index]; }
        inline keys_array& get_keys_array(void) { return Input::keys; }
        inline const keys_array& get_keys_array(void) const { return Input::keys; }

        inline bool& get_mb(index_t index) { return Input::mouse_buttons[index]; }
        inline const bool& get_mb(index_t index) const { return Input::mouse_buttons[index]; }
        inline mb_array& get_mb_array(void) { return Input::mouse_buttons; }
        inline const mb_array& get_mb_array(void) const { return Input::mouse_buttons; }

        inline void set_key(index_t index, bool value) { Input::keys[index] = value; }
        inline void set_mb(index_t index, bool value) { Input::mouse_buttons[index] = value; }

        inline void set_keys(bool value) { keys.fill(value); }
        inline void set_mb(bool value) { mouse_buttons.fill(value); }
        inline void reset(void) { keys.fill(false); mouse_buttons.fill(false); }
    private:
        keys_array keys;
        mb_array mouse_buttons;
    };
    using keys_array = Input::keys_array;
    using mb_array = Input::mb_array;
} // namespace neo

#endif // NEO_INPUT_HPP