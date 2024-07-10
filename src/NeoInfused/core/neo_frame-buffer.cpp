#include "neo_pch.hpp"
#include "NeoInfused/core/neo_frame-buffer.hpp"

namespace neo {
	FrameBuffer* FrameBuffer::m_This = nullptr;

	FrameBuffer::FrameBuffer(void)
	: m_Buffer(nullptr), m_InsertIndex(0), m_Size(0) {
		NEO_ASSERT(!FrameBuffer::m_This, "Cannot create multiple instances of FrameBuffer!");
		FrameBuffer::m_This = this;
	}
	FrameBuffer::~FrameBuffer(void) {
		free(m_Buffer);
		FrameBuffer::m_This = nullptr;
	}

	void FrameBuffer::initialize(size_t size) {
		m_Buffer = (byte_t*)malloc(size);
		NEO_ASSERT(m_Buffer, "Failed to allocate FrameBuffer::m_Buffer!");
		m_Size = size;
	}
	void FrameBuffer::reallocate(size_t new_size) {
		m_Buffer = (byte_t*)realloc(m_Buffer, new_size);
		NEO_ASSERT(m_Buffer, "Failed to reallocate FrameBuffer::m_Buffer!");
	}
	void FrameBuffer::flush(void) {
		m_InsertIndex = 0;
	}

	void* FrameBuffer::add(size_t size) {
		NEO_ASSERT((m_InsertIndex + size) < m_Size, "FrameBuffer::add({0}): out of bounds!", size);
		m_InsertIndex += size;
		return (void*)(m_Buffer + (m_InsertIndex - size));
	}
	void* FrameBuffer::at(size_t index) {
		NEO_ASSERT(index < m_Size, "FrameBuffer::at({0}): out of bounds!", index);
		return (void*)(m_Buffer + index);
	}
}
