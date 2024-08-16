#include "neo_pch.hpp"
#include "NeoInfused/graphics/neo_mesh.hpp"

#include "NeoInfused/graphics/gl/neo-gl_mesh.hpp"

namespace neo {
	Mesh* Mesh::Create(void* vertex_data,
					   uint32_t vertex_data_size,
					   const VertexDataLayout& vertex_data_layout,
					   const std::initializer_list<uint32_t>& indices)
	{
		if (Context::API() == NEO_RENDERERAPI_OPENGL)
			return new gl::Mesh(vertex_data, vertex_data_size, vertex_data_layout, indices);
		return nullptr;
	}
}
