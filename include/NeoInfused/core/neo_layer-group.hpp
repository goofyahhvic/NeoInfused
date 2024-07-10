#if !defined(NEO_LAYERGROUP_HPP)
#define NEO_LAYERGROUP_HPP

#include "NeoInfused/core/neo_layer.hpp"

namespace neo {
    class LayerGroup {
    public:
        using Layers = std::vector<Layer*>;
        LayerGroup(void) = default;
        ~LayerGroup(void);
    public:
        template<typename T, typename... _Args>
        inline T* create(_Args&&... __args) { return (T*)this->push(new T(std::forward<_Args>(__args)...)); }
        Layer* push(Layer* layer);
        void pop(size_t index);

        void set_priority(int32_t new_priority, size_t index);
        void resort(void);

        size_t find_first_of(const Layer* layer) const;
        size_t find_last_of(const Layer* layer) const;

        inline Layers::iterator begin(void) { return m_Layers.begin(); }
        inline Layers::iterator end(void) { return m_Layers.end(); }

        inline Layers::reverse_iterator rbegin(void) { return m_Layers.rbegin(); }
        inline Layers::reverse_iterator rend(void) { return m_Layers.rend(); }

        inline Layers::const_iterator cbegin(void) const { return m_Layers.cbegin(); }
        inline Layers::const_iterator cend(void) const { return m_Layers.cend(); }

        inline Layers::const_reverse_iterator crbegin(void) const { return m_Layers.crbegin(); }
        inline Layers::const_reverse_iterator crend(void) const { return m_Layers.crend(); }

        inline size_t size(void) const { return m_Layers.size(); }
        inline size_t capacity(void) const { return m_Layers.capacity(); }

        inline Layer* operator[](size_t index) const { return m_Layers[index]; }
        inline Layer* at(size_t index) { return m_Layers.at(index); }
        
        inline bool empty(void) const { return m_Layers.empty(); }
    private:
        Layers m_Layers;
    };
    
} // namespace neo

#endif // NEO_LAYERGROUP_HPP