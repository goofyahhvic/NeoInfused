#if !defined(NEO_LAYER_HPP)
#define NEO_LAYER_HPP

namespace neo {
    class Layer {
    public:
        Layer(bool enabled = true) : m_Enabled(enabled) {}
        virtual ~Layer(void) = default;
    public:
        virtual void update(void) {}
        virtual void draw(void) {}
        // returns if event should be passed down or not
        virtual bool handle_event(SDL_Event* e) { return true; }
        
        virtual inline void enable(void) { this->m_Enabled = true; }
        virtual inline void disable(void) { this->m_Enabled = false; }
        bool enabled(void) const { return this->m_Enabled; }
        inline operator bool() { return this->m_Enabled; }
    protected:
        bool m_Enabled;
    private:
    };
} // namespace neo 

#endif // NEO_LAYER_HPP
