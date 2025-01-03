#if !defined(NEO_LAYER_HPP)
#define NEO_LAYER_HPP

#include "NeoInfused/Core/Neo_Core.hpp"

namespace neo {
    class Layer {
        friend class LayerGroup;
    public:
        Layer(int64_t priority, bool enabled = true) : m_Priority(priority), m_Enabled(true) {}
        virtual ~Layer(void) = default;
    public:
        virtual void update(void) {}
        virtual void draw(void) {}
        // returns true if event should be passed down
        virtual bool handle_event(SDL_Event* e) { return true; }
        
        inline void enable(void) { m_Enabled = true; }
        inline void disable(void) { m_Enabled = false; }
        inline void set_enabled(bool value) { m_Enabled = value; }
        inline bool enabled(void) const { return m_Enabled; }
        inline int64_t priority(void) const { return m_Priority; }

        inline bool operator>(const Layer& r)  const { return (m_Priority > r.m_Priority); }
        inline bool operator>=(const Layer& r) const { return (m_Priority >= r.m_Priority); }
        inline bool operator<(const Layer& r)  const { return (m_Priority < r.m_Priority); }
        inline bool operator<=(const Layer& r) const { return (m_Priority <= r.m_Priority); }
        inline bool operator==(const Layer& r) const { return (m_Priority == r.m_Priority); }
        inline bool operator!=(const Layer& r) const { return (m_Priority != r.m_Priority); }

        inline operator int64_t() const { return m_Priority; }
        inline operator bool() const { return m_Enabled; }
    protected:
        bool m_Enabled;
    private:
        int64_t m_Priority;
    };
} // namespace neo 

#endif // NEO_LAYER_HPP
