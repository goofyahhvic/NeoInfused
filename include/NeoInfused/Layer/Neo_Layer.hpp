#if !defined(NEO_LAYER_HPP)
#define NEO_LAYER_HPP

namespace neo {
    class Layer {
    public:
#if !defined(NEO_CONFIG_DIST)
        Layer(const std::string& debug_name = "Layer", bool enabled = true) : m_DebugName(debug_name), m_Enabled(enabled) {}
#else
        Layer(bool enabled = true) : m_Enabled(enabled) {}
#endif // NEO_CONFIG_DIST
        virtual ~Layer(void) = default;
    public:
        virtual void update(void) {}
        virtual void draw(void) {}
        // returns if event should be passed down or not
        virtual bool handle_event(SDL_Event* e) { return true; }
#if !defined(NEO_CONFIG_DIST)
        const std::string& get_name(void) const { return Layer::m_DebugName; }
#else
        const std::string& get_name(void) const { return std::string(""); }
#endif // NEO_CONFIG_DIST
        virtual inline void enable(void) { this->m_Enabled = true; }
        virtual inline void disable(void) { this->m_Enabled = false; }
        bool enabled(void) const { return this->m_Enabled; }
    protected:
        bool m_Enabled;
    private:
#if !defined(NEO_CONFIG_DIST)
        std::string m_DebugName;
#endif // NEO_CONFIG_DIST
    };
} // namespace neo 

#endif // NEO_LAYER_HPP