#if !defined(NEO_ENTITY_HPP)
#define NEO_ENTITY_HPP

#include "NeoInfused/Core/Neo_Core.hpp"

namespace neo {
    class Entity {
    public:
        Entity(void) : m_ComponentContainer(nullptr), m_Slots(0) {}
        Entity(size_t component_slots);
        ~Entity(void);

        void clone(const Entity* src);
    public:
        void* add_component(void* component, size_t slot);
        void* get(size_t component_slot) const;
        
        template<typename T> inline T* get(size_t component_slot) { return (T*)(m_ComponentContainer[component_slot]); }
        template<typename T> const T* get(size_t component_slot) const { return (const T*)(m_ComponentContainer[component_slot]); }

        void grow_container(size_t slots_amount);
        void fill_container(byte_t what = 0);
        void fill_container(void* what = nullptr);

        inline size_t slots(void) const { return m_Slots; }
        inline void** container(void) { return m_ComponentContainer; }
    private:
        void** m_ComponentContainer;
        size_t m_Slots;
    };
} // namespace neo

#endif // NEO_ENTITY_HPP