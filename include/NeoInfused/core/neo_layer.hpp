#if !defined(NEO_LAYER_HPP)
#define NEO_LAYER_HPP

#include "NeoInfused/core/neo_event.hpp"

enum neo_layer_state_t {
	NEO_LAYERSTATE_NONE = 0,
	NEO_LAYERSTATE_ENABLED = NEO_BIT(0),  // receives input
	NEO_LAYERSTATE_UPDATABLE = NEO_BIT(1),
	NEO_LAYERSTATE_VISIBLE = NEO_BIT(2),
	NEO_LAYERSTATE_ALL = (
		NEO_LAYERSTATE_ENABLED |
		NEO_LAYERSTATE_UPDATABLE |
		NEO_LAYERSTATE_VISIBLE
	)
};

namespace neo {
	namespace layer {
		using state_t = neo_layer_state_t;
		struct layer_t {
			friend class storage_t;
			inline auto operator<=>(const layer_t& other) const { return priority <=> other.priority; }
			inline bool operator==(const layer_t& other) const { return priority == other.priority; }

			state_t state;
			int64_t priority;
			std::function<void(event_t& e)> on_event;
			std::function<void(void)> update;
			std::function<void(void)> draw;
		};
	} // namespace layer
	using layer_t = layer::layer_t;
} // namespace neo

#endif // NEO_LAYER_HPP