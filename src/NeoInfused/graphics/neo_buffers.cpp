#include "neo_pch.hpp"
#include "NeoInfused/graphics/neo_buffers.hpp"

#include "NeoInfused/graphics/gl/neo-gl_buffers.hpp"

namespace neo {
	VertexBuffer* VertexBuffer::Create(void* vertices, uint32_t size) {
		if (Context::API() == NEO_RENDERERAPI_OPENGL)
			return new gl::VertexBuffer(vertices, size);
		return nullptr;
	}

	IndexBuffer* IndexBuffer::Create(uint32_t* vertices, uint32_t count) {
		if (Context::API() == NEO_RENDERERAPI_OPENGL)
			return new gl::IndexBuffer(vertices, count);
		return nullptr;
	}
}
