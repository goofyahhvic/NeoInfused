#if !defined(NEO_LAYER_HPP)
#define NEO_LAYER_HPP

namespace neo {
    class Layer {
        friend class LayerGroup;
    public:
        Layer(float priority) : m_Priority(priority) {}
        virtual ~Layer(void) = default;
    public:
        virtual void update(void) {}
        virtual void draw(void) {}
        // returns true if event should be passed down
        virtual bool handle_event(SDL_Event* e) { return true; }
        
        inline bool enabled(void) const { return (m_Priority >= 0.0f); }
        inline float priority(void) const { return m_Priority; }

        inline bool operator>(const Layer& r)  const { return (m_Priority > r.m_Priority); }
        inline bool operator>=(const Layer& r) const { return (m_Priority >= r.m_Priority); }
        inline bool operator<(const Layer& r)  const { return (m_Priority < r.m_Priority); }
        inline bool operator<=(const Layer& r) const { return (m_Priority <= r.m_Priority); }
        inline bool operator==(const Layer& r) const { return (m_Priority == r.m_Priority); }
        inline bool operator!=(const Layer& r) const { return (m_Priority != r.m_Priority); }

        inline operator float() const { return m_Priority; }
    protected:
        float m_Priority;
    };
} // namespace neo 

#endif // NEO_LAYER_HPP
