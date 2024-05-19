#if !defined(NEO_LAYER_HPP)
#define NEO_LAYER_HPP

namespace neo {
    class Layer {
    public:
#if !defined(NEO_CONFIG_DIST)
        Layer(const std::string& _debug_name = "Layer", bool enabled = true) : debug_name(_debug_name), _enabled(enabled) {}
#else
        Layer(bool enabled = true) : _enabled(enabled) {}
#endif // NEO_CONFIG_DIST
        virtual ~Layer(void) = default;
    public:
        virtual void update(void) {}
        virtual void draw(void) {}
        // returns if event should be passed down or not
        virtual bool handle_event(SDL_Event* e) { return true; }
#if !defined(NEO_CONFIG_DIST)
        const std::string& get_name(void) const { return Layer::debug_name; }
#else
        const std::string& get_name(void) const { return std::string(""); }
#endif // NEO_CONFIG_DIST
        virtual inline void enable(void) { this->_enabled = true; }
        virtual inline void disable(void) { this->_enabled = false; }
        bool enabled(void) const { return this->_enabled; }
    protected:
        bool _enabled;
    private:
#if !defined(NEO_CONFIG_DIST)
        std::string debug_name;
#endif // NEO_CONFIG_DIST
    };
} // namespace neo 

#endif // NEO_LAYER_HPP