#if !defined(NEO_BUFFERS_HPP)
#define NEO_BUFFERS_HPP

#include "neo_context.hpp"

namespace neo {
	struct VertexBufferElement {
		uint32_t count;
		Type type;
		bool normalized = false;
		uint32_t size = SizeOf(type) * count;
	};
	using VertexBufferLayout = std::initializer_list<VertexBufferElement>;

	class VertexBuffer {
	public:
		VertexBuffer(void) = default;
		virtual ~VertexBuffer(void) = default;
		static VertexBuffer* Create(void* vertices, uint32_t size);

		virtual void set_layout(const VertexBufferLayout& layout) = 0;
		virtual void bind(void) const = 0;
	};

	class IndexBuffer {
	public:
		IndexBuffer(void) = default;
		virtual ~IndexBuffer(void) = default;
		static IndexBuffer* Create(uint32_t* indices, uint32_t count);

		virtual void bind(void) const = 0;
		virtual uint32_t count(void) const = 0;
	};
}

#endif // NEO_BUFFERS_HPP