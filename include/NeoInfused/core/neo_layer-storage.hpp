#if !defined(NEO_LAYER_STORAGE_HPP)
#define NEO_LAYER_STORAGE_HPP

#include "NeoInfused/core/neo_layer.hpp"

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

        template<typename T, typename... _Args>
        inline T* create_layer(_Args&&... __args) { return (T*)this->_push(new T(std::forward<_Args>(__args)...)); }
        void destroy_layer(size_t index);

        void set_priority(int32_t new_priority, size_t index);

        inline size_t size(void) const { return m_Layers.size(); }

        inline Layer* operator[](size_t index) const { return m_Layers[index]; }
        inline Layer* at(size_t index) { return m_Layers.at(index); }
        
        inline bool empty(void) const { return m_Layers.empty(); }

        size_t find_first_of(const Layer* layer) const;
        size_t find_last_of(const Layer* layer) const;

        inline iterator begin(void) { return m_Layers.begin(); }
        inline const_iterator begin(void) const { return m_Layers.begin(); }
        inline const_iterator cbegin(void) const { return m_Layers.cbegin(); }

        inline iterator end(void) { return m_Layers.end(); }
        inline const_iterator end(void) const { return m_Layers.end(); }
        inline const_iterator cend(void) const { return m_Layers.cend(); }

        inline reverse_iterator rbegin(void) { return m_Layers.rbegin(); }
        inline const_reverse_iterator rbegin(void) const { return m_Layers.rbegin(); }
        inline const_reverse_iterator crbegin(void) const { return m_Layers.crbegin(); }

        inline reverse_iterator rend(void) { return m_Layers.rend(); }
        inline const_reverse_iterator rend(void) const { return m_Layers.rend(); }
        inline const_reverse_iterator crend(void) const { return m_Layers.crend(); }
    private:
        Layer* _push(Layer* layer);
    private:
        std::vector<Layer*> m_Layers;
    };
    
} // namespace neo

#endif // NEO_LAYER_STORAGE_HPP