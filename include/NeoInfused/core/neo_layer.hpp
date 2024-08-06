#if !defined(NEO_LAYER_HPP)
#define NEO_LAYER_HPP

#include "NeoInfused/core/neo_event.hpp"

enum neo_LayerState {
    NEO_LAYERSTATE_NONE      = 0,
    NEO_LAYERSTATE_ENABLED   = NEO_BIT(0),  // receives input
    NEO_LAYERSTATE_UPDATABLE = NEO_BIT(1),
    NEO_LAYERSTATE_VISIBLE   = NEO_BIT(2),
    NEO_LAYERSTATE_ALL       = (NEO_LAYERSTATE_ENABLED | NEO_LAYERSTATE_UPDATABLE | NEO_LAYERSTATE_VISIBLE)
};

namespace neo {
    using LayerState = neo_LayerState;
    class Layer {
        friend class LayerStorage;
    public:
        Layer(int32_t priority, uint8_t _state = NEO_LAYERSTATE_ALL)
        : m_Priority(priority), state(_state) {}
        virtual ~Layer(void) = default;

        virtual void on_event(const Event& e) = 0;
        virtual void update(void) = 0;
        virtual void draw(size_t window_id) = 0;

        inline int32_t priority(void) const { return m_Priority; }
    public:
        uint8_t state;
    private:
        int32_t m_Priority;
    };
} // namespace neo

#endif // NEO_LAYER_HPP