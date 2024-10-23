#if !defined(NEO_LAYER_STORAGE_HPP)
#define NEO_LAYER_STORAGE_HPP

#include "../core/neo_layer.hpp"

namespace neo {
	namespace layer {
		class storage_t {
		public:
			using layers_t = std::vector<layer_t*>;
			using iterator_t = layers_t::iterator;
			using const_iterator_t = layers_t::const_iterator;
			using reverse_iterator_t = layers_t::reverse_iterator;
			using const_reverse_iterator_t = layers_t::const_reverse_iterator;
		public:
			storage_t(void) = default;
			~storage_t(void);
			void clear(void);

			template<typename T, typename... _Args>
			inline T* create_layer(_Args&&... __args) { return (T*)this->_push(new T(std::forward<_Args>(__args)...)); }
			void destroy_layer(layer_t* layer);

			void set_priority(layer_t* layer, int32_t new_priority);

			[[nodiscard]] inline size_t size(void) const { return m_Layers.size(); }
			[[nodiscard]] inline size_t capacity(void) const { return m_Layers.capacity(); }
			[[nodiscard]] inline bool empty(void) const { return m_Layers.empty(); }

			[[nodiscard]] inline layer_t* operator[](size_t index) { return m_Layers[index]; }
			[[nodiscard]] inline const layer_t* operator[](size_t index) const { return m_Layers[index]; }

			[[nodiscard]] inline iterator_t begin(void) { return m_Layers.begin(); }
			[[nodiscard]] inline const_iterator_t begin(void) const { return m_Layers.begin(); }
			[[nodiscard]] inline const_iterator_t cbegin(void) const { return m_Layers.cbegin(); }

			[[nodiscard]] inline iterator_t end(void) { return m_Layers.end(); }
			[[nodiscard]] inline const_iterator_t end(void) const { return m_Layers.end(); }
			[[nodiscard]] inline const_iterator_t cend(void) const { return m_Layers.cend(); }

			[[nodiscard]] inline reverse_iterator_t rbegin(void) { return m_Layers.rbegin(); }
			[[nodiscard]] inline const_reverse_iterator_t rbegin(void) const { return m_Layers.rbegin(); }
			[[nodiscard]] inline const_reverse_iterator_t crbegin(void) const { return m_Layers.crbegin(); }

			[[nodiscard]] inline reverse_iterator_t rend(void) { return m_Layers.rend(); }
			[[nodiscard]] inline const_reverse_iterator_t rend(void) const { return m_Layers.rend(); }
			[[nodiscard]] inline const_reverse_iterator_t crend(void) const { return m_Layers.crend(); }
		private:
			layer_t* _push(layer_t* layer);
			inline void _resort(void) { std::sort(m_Layers.begin(), m_Layers.end(), _Greater); }
			[[nodiscard]] static bool _Greater(layer_t* left, layer_t* right);
		private:
			layers_t m_Layers;
		};
	} // namespace layer
} // namespace neo

#endif // NEO_LAYER_STORAGE_HPP