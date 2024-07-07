#if !defined(NEO_OBJECT_HPP)
#define NEO_OBJECT_HPP

#include "NeoInfused/neo_core.hpp"

namespace neo {
    class Object {
    public:
        Object(void) : m_ComponentContainer(nullptr), m_Slots(0) {}
        Object(size_t component_slots);
        ~Object(void);

        void clone(const Object* src);
    public:
        void* insert_component(void* component, size_t slot);
        void* get(size_t component_slot) const;

        template<typename T, typename... _Args>
        inline T* insert_new_component(_Args&&... __args, size_t slot) {
            T* component = new T(std::forward<_Args>(__args)...);
            m_ComponentContainer[slot] = component;
            return component;
        }
        template<typename T>
        inline void delete_component(size_t slot) {
            delete (T*)(m_ComponentContainer[slot]);
        }
        
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

#endif // NEO_OBJECT_HPP