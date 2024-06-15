#include "Neo_PCH.hpp"
#include "NeoInfused/Layer/Neo_LayerGroup.hpp"

namespace neo {
    static bool greater(Layer* l1, Layer* l2) {
        return (l1->operator>(*l2));
    }
    void LayerGroup::resort(void) {
        std::sort(m_Layers.begin(), m_Layers.end(), greater);
    }

    LayerGroup::~LayerGroup(void) {
        for (auto layer : m_Layers)
            delete layer;
        m_Layers.clear();
    }
    Layer* LayerGroup::push(Layer* layer) {
        m_Layers.push_back(layer);
        std::sort(m_Layers.begin(), m_Layers.end(), greater);
        return layer;
    }
    void LayerGroup::pop(index_t index) {
        delete m_Layers[index];
        m_Layers.erase(m_Layers.begin() + index);
    }

    void LayerGroup::set_priority(float new_priority, index_t index) {
        m_Layers[index]->m_Priority = new_priority;
        std::sort(m_Layers.begin(), m_Layers.end(), greater);
    }

    index_t LayerGroup::find_first_of(const Layer* layer) const {
        index_t i = 0;
        for (auto it = m_Layers.begin(); it != m_Layers.end(); it++) {
            if ((*it) == layer)
                return i;
            i++;
        }
        NEO_ASSERT(0, "Failed to find element in LayerGroup!");
        return NEO_INDEX_MAX;
    }

    index_t LayerGroup::find_last_of(const Layer* layer) const {
        index_t i = m_Layers.size();
        for (auto it = m_Layers.rbegin(); it != m_Layers.rend(); it++) {
            if ((*it) == layer)
                return i-1;
            i--;
        }
        NEO_ASSERT(0, "Failed to find element in LayerGroup!");
        return NEO_INDEX_MAX;
    } 
} // namespace neo
