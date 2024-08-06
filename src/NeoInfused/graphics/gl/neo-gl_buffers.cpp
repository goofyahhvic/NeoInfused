#include "neo_pch.hpp"
#include "NeoInfused/graphics/gl/neo-gl_buffers.hpp"

namespace neo::gl {
	// -------------- [VertexBuffer] -------------- \\
	// -------------------------------------------- \\

	VertexBuffer::VertexBuffer(void* vertices, uint32_t size) {
		glCreateVertexArrays(1, &m_VAO);
		glBindVertexArray(m_VAO);

		glCreateBuffers(1, &m_VBO);
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
		glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
	}
	VertexBuffer::~VertexBuffer(void) {
		glDeleteBuffers(1, &m_VBO);
		glDeleteVertexArrays(1, &m_VAO);
	}

	void VertexBuffer::set_layout(const VertexBufferLayout& layout) {
		glBindVertexArray(m_VAO);

		uint32_t stride = 0;
		for (VertexBufferElement vb_element : layout) {
			stride += vb_element.size;
		}

		uint32_t i = 0;
		uint64_t offset = 0;
		for (const VertexBufferElement& vb_element : layout) {
			glEnableVertexAttribArray(i);
			glVertexAttribPointer(i, vb_element.count, (uint32_t)vb_element.type, vb_element.normalized, stride, (void*)offset);

			offset += vb_element.size;
			i++;
		}
	}
	void VertexBuffer::bind(void) const {
		glBindVertexArray(m_VAO);
	}

	// -------------- [IndexBuffer] -------------- \\
	// ------------------------------------------- \\

	IndexBuffer::IndexBuffer(uint32_t* indices, uint32_t count)
	: m_Count(count) {
		glCreateBuffers(1, &m_IBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), indices, GL_STATIC_DRAW);
	}
	IndexBuffer::~IndexBuffer(void) {
		glDeleteBuffers(1, &m_IBO);
	}

	void IndexBuffer::bind(void) const {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
	}
}
