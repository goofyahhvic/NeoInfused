#include "neo_pch.hpp"
#include "NeoInfused/graphics/gl/neo-gl_mesh.hpp"

#define VERTEX 0
#define INDEX 1

namespace neo::gl {
	Mesh::Mesh(void* vertex_data,
			   uint32_t vertex_data_size,
			   const VertexDataLayout& vertex_data_layout,
			   const std::initializer_list<uint32_t>& indices)
	: m_IndexCount(indices.size())
	{
		glCreateVertexArrays(1, &m_VertexArray);
		glBindVertexArray(m_VertexArray);

		glCreateBuffers(2, m_Buffers);

		glBindBuffer(GL_ARRAY_BUFFER, m_Buffers[VERTEX]);
		glBufferData(GL_ARRAY_BUFFER, vertex_data_size, vertex_data, GL_STATIC_DRAW);

		uint32_t stride = 0;
		for (const VertexBufferElement& vb_element : vertex_data_layout)
			stride += vb_element.size;

		uint32_t i = 0;
		uint64_t offset = 0;
		for (const VertexBufferElement& vb_element : vertex_data_layout)
		{
			glEnableVertexAttribArray(i);
			glVertexAttribPointer(i, vb_element.count, (uint32_t)vb_element.type, vb_element.normalized, stride, (void*)offset);

			offset += vb_element.size;
			i++;
		}

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Buffers[INDEX]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_IndexCount * sizeof(uint32_t), indices.begin(), GL_STATIC_DRAW);
	}
	Mesh::~Mesh(void)
	{
		glDeleteBuffers(2, m_Buffers);
		glDeleteVertexArrays(1, &m_VertexArray);
	}

	void Mesh::draw(void) const
	{
		glBindVertexArray(m_VertexArray);
		glDrawElements(GL_TRIANGLES, m_IndexCount, GL_UNSIGNED_INT, nullptr);
	}
}
