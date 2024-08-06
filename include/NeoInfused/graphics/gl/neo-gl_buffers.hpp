#if !defined(NEO_GL_BUFFERS_HPP)
#define NEO_GL_BUFFERS_HPP

#include "../neo_buffers.hpp"

namespace neo::gl {
	class VertexBuffer : public neo::VertexBuffer {
	public:
		VertexBuffer(void* vertices, uint32_t size);
		~VertexBuffer(void);

		void bind(void) const;
		void set_layout(const VertexBufferLayout& layout);
	private:
		uint32_t m_VBO, m_VAO;
	};

	class IndexBuffer : public neo::IndexBuffer {
	public:
		IndexBuffer(uint32_t* indices, uint32_t count);
		~IndexBuffer(void);

		void bind(void) const;
		inline uint32_t count(void) const { return m_Count; }
	private:
		uint32_t m_IBO, m_Count;
	};
}

#endif // NEO_GL_BUFFERS_HPP