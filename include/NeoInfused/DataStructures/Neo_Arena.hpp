#if !defined(NEO_ARENA_HPP)
#define NEO_ARENA_HPP

#include "NeoInfused/Core/Neo_Core.hpp"

namespace neo {
    template<typename T>
    class TypedArena {
    public:
        TypedArena(void) : m_Data(nullptr), m_Size(0), m_InsertIndex(0) {}
        TypedArena(size_t elements) { m_Data = (T*) malloc(elements * sizeof(T)); m_Size = elements; m_InsertIndex = 0; }
        void destroy(void) { if (!m_Data) return; free(m_Data); m_Data = nullptr; }
        ~TypedArena() { this->destroy(); }

        inline size_t push_back(const T& data) { m_Data[m_InsertIndex] = data; m_InsertIndex++; return m_InsertIndex-1; }
        inline size_t push_back(const T* data) { m_Data[m_InsertIndex] = *data; m_InsertIndex++; return m_InsertIndex-1; }

        size_t find_first_of(const T& data) const {
            T* it = m_Data;
            for (index32_t i = 0; i < m_InsertIndex; i++) {
                if (*it == data)
                    return i;
                it = &(m_Data[i+1]);
            }
            return SIZE_MAX;
        }
        size_t find_last_of(const T& data) const {
            T* it = &(m_Data[m_InsertIndex-1]);
            for (index32_t i = m_InsertIndex; i > 0; i--) {
                if (*it == data)
                    return (index32_t) i-1;
                it = &(m_Data[i-2]);
            }
            return SIZE_MAX;
        }

        inline T& operator[](size_t index) { NEO_ASSERT(index < m_Size, "index {0} is out of bounds! size of arena: {1}", index, m_Size); return m_Data[index]; }
        inline const T& operator[](size_t index) const { NEO_ASSERT(index < m_Size, "index {0} is out of bounds! size of arena: {1}", index, m_Size); return m_Data[index]; }

        inline size_t size() const { return m_Size; }
        inline size_t get_insert_index() const { return m_InsertIndex; }
    private:
        T* m_Data;
        size_t m_Size, m_InsertIndex;
    };
} // namespace neo

#endif // NEO_ARENA_HPP