#if !defined(NEO_LAYER_HPP)
#define NEO_LAYER_HPP

#include "NeoInfused/core/neo_event.hpp"

enum neo_layer_state_t {
	NEO_LAYERSTATE_NONE = 0,
	NEO_LAYERSTATE_ENABLED = NEO_BIT(0),  // receives input
	NEO_LAYERSTATE_UPDATABLE = NEO_BIT(1),
	NEO_LAYERSTATE_VISIBLE = NEO_BIT(2),
	NEO_LAYERSTATE_ALL = (NEO_LAYERSTATE_ENABLED | NEO_LAYERSTATE_UPDATABLE | NEO_LAYERSTATE_VISIBLE)
};

namespace neo {
	namespace layer {
		using state_t = neo_layer_state_t;
		class layer_t {
			friend class storage_t;
		public:
			layer_t(int32_t priority, uint8_t _state = NEO_LAYERSTATE_ALL)
			: m_Priority(priority), state(_state) {}
			virtual ~layer_t(void) = default;

			virtual void on_event(event_t& e) = 0;
			virtual void update(void) = 0;
			virtual void draw(void) = 0;

			inline int32_t priority(void) const { return m_Priority; }
		public:
			uint8_t state;
		private:
			int32_t m_Priority;
		};
	} // namespace layer
	using layer_t = layer::layer_t;
} // namespace neo

#endif // NEO_LAYER_HPP