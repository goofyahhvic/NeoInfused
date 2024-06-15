#if !defined(NEO_BUFFER_HPP)
#define NEO_BUFFER_HPP

#include "NeoInfused/Core/Neo_Core.hpp"

namespace neo {
    // reference counted buffer
    class Buffer {
    public:
        Buffer(void) : m_Buffer(nullptr), m_Size(0), m_RefCount(nullptr) {}
        Buffer(size_t size);

        Buffer(const Buffer& buf);
        void operator=(const Buffer& buf);

        void destroy(void);
        ~Buffer(void);
    public:
        void grow(size_t growth_size);
        void resize(size_t new_size);

        template<typename T>
        inline T& get(size_t index) { NEO_ASSERT((index < (m_Size / sizeof(T))), "index {0} is out of bounds! size of buffer: {1}", index, m_Size/sizeof(T)); return ((T*)m_Buffer)[index]; }

        template<typename T>
        inline const T& get(size_t index) const { NEO_ASSERT((index < (m_Size / sizeof(T))), "index {0} is out of bounds! size of buffer: {1}", index, m_Size/sizeof(T)); return ((T*)m_Buffer)[index]; }

        inline void* buffer(void) { return m_Buffer; }

        template<typename T>
        inline size_t size(void) { return m_Size / sizeof(T); }
        inline size_t size(void) { return m_Size; }
    private:
        void* m_Buffer;
        size_t m_Size;
        size_t* m_RefCount;
    };

    // a typed reference of a non typed buffer
    template<typename T>
    class TypedBufRef {
    public:
        TypedBufRef(Buffer& buf) : m_Buffer(buf) {}
        ~TypedBufRef(void) = default;
    public:
        inline void grow(size_t growth_size) { m_Buffer.grow(growth_size * sizeof(T)); }
        inline void resize(size_t new_size)  { m_Buffer.resize(new_size * sizeof(T)); }

        inline T& operator[](size_t index) { return m_Buffer.get<T>(index); }
        inline const T& operator[](size_t index) const { return m_Buffer.get<T>(index); }

        inline T& operator*(void) { return m_Buffer.get<T>(0); }
        inline const T& operator*(void) const { return m_Buffer.get<T>(0); }

        inline T* operator->(void) { return &(m_Buffer.get<T>(0)); }
        inline const T* operator->(void) const { return &(m_Buffer.get<T>(0)); }

        Buffer& buffer(void) { return m_Buffer; }
        inline size_t size(void) { return m_Buffer.size<T>(); }
    private:
        Buffer& m_Buffer;
    };

    // reference counted and typed buffer
    template<typename T>
    class TypedBuf {
    public:
        TypedBuf(void) : m_Buffer(nullptr), m_Size(0), m_RefCount(nullptr) {}
        TypedBuf(size_t size) {
            m_Size = size;
            m_Buffer = (T*) malloc(size * sizeof(T));

            m_RefCount = (size_t*) malloc(sizeof(size_t));
            *m_RefCount = 1;
        }
        TypedBuf(const TypedBuf& buf) {
            m_Buffer = buf.m_Buffer;
            m_Size = buf.m_Size;
            m_RefCount = buf.m_RefCount;
            (*m_RefCount)++;
        }
        inline void operator=(const TypedBuf& buf) {
            m_Buffer = buf.m_Buffer;
            m_Size = buf.m_Size;
            m_RefCount = buf.m_RefCount;
            (*m_RefCount)++;
        }

        inline void destroy(void) {
            if (!m_Size) return;

            m_Size = 0;
            free(m_Buffer);
            m_Buffer = nullptr;

            (*m_RefCount) = 0;
            free(m_RefCount);
            m_RefCount = nullptr;
        }
        ~TypedBuf(void) {
            (*m_RefCount)--;
            if (!(*m_RefCount))
                this->destroy();
        }
    public:
        inline void grow(size_t growth_size) { m_Size += growth_size; m_Buffer = realloc(m_Buffer, m_Size * sizeof(T)); }
        inline void resize(size_t new_size)  { m_Size = new_size; m_Buffer = realloc(m_Buffer, new_size * sizeof(T)); }

        inline T& operator[](size_t index) { NEO_ASSERT(index < m_Size, "index {0} is out of bounds! size of buffer: {1}", index, m_Size); return m_Buffer[index]; }
        inline const T& operator[](size_t index) const { NEO_ASSERT(index < m_Size, "index {0} is out of bounds! size of buffer: {1}", index, m_Size); return m_Buffer[index]; }

        inline T& operator*(void) { return *m_Buffer; }
        inline const T& operator*(void) const { return *m_Buffer; }

        inline T* operator->(void) { return m_Buffer; }
        inline const T* operator->(void) const { return m_Buffer; }

        inline T* buffer(void) { return m_Buffer; }
        inline size_t size(void) { return m_Size; }

        inline size_t get_ref_count(void) const { return *m_RefCount; }
    private:
        T* m_Buffer;
        size_t m_Size;
        size_t* m_RefCount;
    };
} // namespace neo

#endif // NEO_BUFFER_HPP
