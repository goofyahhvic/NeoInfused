#if !defined(NEO_INPUT_LAYER_HPP)
#define NEO_INPUT_LAYER_HPP

#include "./Neo_Layer.hpp"
#include "./Neo_Input.hpp"

namespace neo {
    class InputLayer : public Layer {
    public:
#if !defined(NEO_CONFIG_DIST)
        InputLayer(const std::string& debug_name = "InputLayer", bool enabled = true);
#else
        InputLayer(bool enabled = true);
#endif // NEO_CONFIG_DIST
        virtual ~InputLayer(void) {}
    public:
        virtual bool handle_event(SDL_Event* e) override;
    protected:
        void _set_input(SDL_Event* e);
    protected:
        Input m_Input;
    };
} // namespace neo


#endif // NEO_INPUT_LAYER_HPP