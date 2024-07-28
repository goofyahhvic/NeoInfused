#include "neo_pch.hpp"
#include "NeoInfused/core/neo_layer-storage.hpp"

namespace neo {
    static bool greater(Layer* l1, Layer* l2) {
        return l1->priority() > l2->priority();
    }

    LayerStorage::~LayerStorage(void) {
        for (auto layer : m_Layers)
            delete layer;
        m_Layers.clear();
    }
    Layer* LayerStorage::_push(Layer* layer) {
        m_Layers.push_back(layer);
        std::sort(m_Layers.begin(), m_Layers.end(), greater);
        return layer;
    }
    void LayerStorage::destroy_layer(size_t index) {
        delete m_Layers[index];
        m_Layers.erase(m_Layers.begin() + index);
    }

    void LayerStorage::set_priority(int32_t new_priority, size_t index) {
        m_Layers[index]->m_Priority = new_priority;
        std::sort(m_Layers.begin(), m_Layers.end(), greater);
    }

    size_t LayerStorage::find_first_of(const Layer* layer) const {
        size_t i = 0;
        for (auto it = m_Layers.begin(); it != m_Layers.end(); it++) {
            if ((*it) == layer)
                return i;
            i++;
        }
        NEO_ASSERT(0, "Failed to find element in LayerStorage!");
        return SIZE_MAX;
    }

    size_t LayerStorage::find_last_of(const Layer* layer) const {
        size_t i = m_Layers.size();
        for (auto it = m_Layers.rbegin(); it != m_Layers.rend(); it++) {
            if ((*it) == layer)
                return i-1;
            i--;
        }
        NEO_ASSERT(0, "Failed to find element in LayerStorage!");
        return SIZE_MAX;
    } 
} // namespace neo
