#include "Neo_PCH.hpp"
#include "NeoInfused/Layer/Neo_LayerStack.hpp"

namespace neo {
    void LayerStack::push_layer(Layer* layer) {
		layers.emplace(layers.begin() + insert_index, layer);
		insert_index++;
	}
	void LayerStack::push_overlay(Layer* overlay) {
		layers.emplace_back(overlay);
	}

	Layer* LayerStack::pop_layer(Layer* layer) {
		auto it = std::find(layers.begin(), layers.end(), layer);
		if (it != layers.end()) {
			layers.erase(it);
			insert_index--;
		}
		return layer;
	}
	Layer* LayerStack::pop_overlay(Layer* overlay) {
		auto it = std::find(layers.begin(), layers.end(), overlay);
		if (it != layers.end()) {
			layers.erase(it);
		}
		return overlay;
	}
} // namespace neo
