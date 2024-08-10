#if !defined(NEO_LAYER_STORAGE_HPP)
#define NEO_LAYER_STORAGE_HPP

#include "../core/neo_layer.hpp"

namespace neo {
	class LayerStorage {
	public:
		using iterator = std::vector<Layer*>::iterator;
		using const_iterator = std::vector<Layer*>::const_iterator;
		using reverse_iterator = std::vector<Layer*>::reverse_iterator;
		using const_reverse_iterator = std::vector<Layer*>::const_reverse_iterator;
	public:
		LayerStorage(void) = default;
		~LayerStorage(void);
		void clear(void);

		template<typename T, typename... _Args>
		inline T* create_layer(_Args&&... __args) { return (T*)this->_push(new T(std::forward<_Args>(__args)...)); }
		void destroy_layer(Layer* layer);

		void set_priority(Layer* layer, int32_t new_priority);

		[[nodiscard]] inline size_t size(void) const { return m_Layers.size(); }

		[[nodiscard]] inline Layer* operator[](size_t index) const { return m_Layers[index]; }
		[[nodiscard]] inline Layer* at(size_t index) { return m_Layers.at(index); }

		[[nodiscard]] inline bool empty(void) const { return m_Layers.empty(); }

		[[nodiscard]] inline iterator begin(void) { return m_Layers.begin(); }
		[[nodiscard]] inline const_iterator begin(void) const { return m_Layers.begin(); }
		[[nodiscard]] inline const_iterator cbegin(void) const { return m_Layers.cbegin(); }

		[[nodiscard]] inline iterator end(void) { return m_Layers.end(); }
		[[nodiscard]] inline const_iterator end(void) const { return m_Layers.end(); }
		[[nodiscard]] inline const_iterator cend(void) const { return m_Layers.cend(); }

		[[nodiscard]] inline reverse_iterator rbegin(void) { return m_Layers.rbegin(); }
		[[nodiscard]] inline const_reverse_iterator rbegin(void) const { return m_Layers.rbegin(); }
		[[nodiscard]] inline const_reverse_iterator crbegin(void) const { return m_Layers.crbegin(); }

		[[nodiscard]] inline reverse_iterator rend(void) { return m_Layers.rend(); }
		[[nodiscard]] inline const_reverse_iterator rend(void) const { return m_Layers.rend(); }
		[[nodiscard]] const_reverse_iterator crend(void) const { return m_Layers.crend(); }
	private:
		Layer* _push(Layer* layer);
		inline void _resort(void) { std::sort(m_Layers.begin(), m_Layers.end(), _Greater); }
		[[nodiscard]] static bool _Greater(Layer* left, Layer* right);
	private:
		std::vector<Layer*> m_Layers;
	};

} // namespace neo

#endif // NEO_LAYER_STORAGE_HPP