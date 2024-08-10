#if !defined(NEO_GL_MESH_HPP)
#define NEO_GL_MESH_HPP

#include "../neo_mesh.hpp"

namespace neo::gl {
	class Mesh : public neo::Mesh {
	public:
		Mesh(void* vertex_data,
			uint32_t vertex_data_size,
			const VertexDataLayout& vertex_data_layout,
			uint32_t* indices,
			uint32_t index_count);
		~Mesh(void);

		void draw(void) const;
	private:
		uint32_t m_VertexArray, m_IndexCount;
		uint32_t m_Buffers[2];
	};
}

#endif // NEO_GL_MESH_HPP