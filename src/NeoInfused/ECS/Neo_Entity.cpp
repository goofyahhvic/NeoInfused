#include "Neo_PCH.hpp"
#include "NeoInfused/ECS/Neo_Entity.hpp"

namespace neo {
    Entity::Entity(size_t component_slots)
        : m_Slots(component_slots), m_ComponentContainer((void**)malloc(component_slots * __SIZEOF_POINTER__)) {
        
    }
    Entity::~Entity(void) {
        free(m_ComponentContainer);
    }
    void Entity::clone(const Entity* src) {
        m_Slots = src->m_Slots;
        m_ComponentContainer = (void**)malloc(m_Slots * __SIZEOF_POINTER__);
        for (int i = 0; i < m_Slots; i++) {
            m_ComponentContainer[i] = src->m_ComponentContainer[i];
        }
    }

    void* Entity::add_component(void* component, size_t slot) {
        m_ComponentContainer[slot] = component;
        return component;
    }
    void* Entity::get(size_t component_slot) const {
        return m_ComponentContainer[component_slot];
    }

    void Entity::grow_container(size_t slots_amount) {
        m_Slots += slots_amount;
        m_ComponentContainer = (void**)realloc(m_ComponentContainer, m_Slots);
    }
    void Entity::fill_container(byte_t what) {
        for (int i = 0; i < m_Slots * __SIZEOF_POINTER__; i++) {
            ((byte_t*)m_ComponentContainer)[i] = what;
        }
    }
    void Entity::fill_container(void* what) {
        for (int i = 0; i < m_Slots; i++) {
            m_ComponentContainer[i] = what;
        }
    }
} // namespace neo
