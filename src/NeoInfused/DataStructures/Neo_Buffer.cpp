#include "Neo_PCH.hpp"
#include "NeoInfused/DataStructures/Neo_Buffer.hpp"

namespace neo {
    Buffer::Buffer(size_t size) {
        m_Size = size;
        m_Buffer = malloc(size);

        m_RefCount = (size_t*) malloc(sizeof(size_t));
        *m_RefCount = 1;
    }
    Buffer::Buffer(const Buffer& buf) {
        m_Buffer = buf.m_Buffer;
        m_Size = buf.m_Size;
        m_RefCount = buf.m_RefCount;
        (*m_RefCount)++;
    }
    void Buffer::operator=(const Buffer& buf) {
        m_Buffer = buf.m_Buffer;
        m_Size = buf.m_Size;
        m_RefCount = buf.m_RefCount;
        (*m_RefCount)++;
    }

    void Buffer::destroy(void) {
        if (!m_Size) return;

        m_Size = 0;
        free(m_Buffer);
        m_Buffer = nullptr;

        (*m_RefCount) = 0;
        free(m_RefCount);
        m_RefCount = nullptr;
    }
    Buffer::~Buffer(void) {
        (*m_RefCount)--;
        if (!(*m_RefCount))
            this->destroy();
    }

    void Buffer::grow(size_t growth_size) {
        m_Size += growth_size;
        realloc(m_Buffer, m_Size);
    }
    void Buffer::resize(size_t new_size) {
        m_Size = new_size;
        realloc(m_Buffer, new_size);
    }
} // namespace neo
