#if !defined(NEO_LAYER_STACK_HPP)
#define NEO_LAYER_STACK_HPP

#include "./Neo_Layer.hpp"

namespace neo {
    class LayerStack {
        using layer_vec = std::vector<Layer*>;
    public:
		LayerStack() = default;
		~LayerStack() = default;
    public:
		// Pushes a layer on top of previous layers, but below the overlays.
		void push_layer(Layer* layer);
		// Pushes a Layer on top everything else.
		void push_overlay(Layer* overlay);
		Layer* pop_layer(Layer* layer);
		Layer* pop_overlay(Layer* overlay);

		inline layer_vec::iterator begin() { return LayerStack::layers.begin(); }
		inline layer_vec::iterator end() { return LayerStack::layers.end(); }
		inline layer_vec::reverse_iterator rbegin() { return LayerStack::layers.rbegin(); }
		inline layer_vec::reverse_iterator rend() { return LayerStack::layers.rend(); }

        inline layer_vec::const_iterator cbegin() const { return LayerStack::layers.cbegin(); }
		inline layer_vec::const_iterator cend() const { return LayerStack::layers.cend(); }
        inline layer_vec::const_reverse_iterator crbegin() const { return LayerStack::layers.crbegin(); }
		inline layer_vec::const_reverse_iterator crend() const { return layers.crend(); }
	private:
		layer_vec layers;
		index32_t insert_index = 0;
    }; 
} // namespace neo

#endif // NEO_LAYER_STACK_HPP