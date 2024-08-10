#if !defined(NEO_MESH_HPP)
#define NEO_MESH_HPP

#include "neo_context.hpp"

namespace neo {
	struct VertexBufferElement {
		uint32_t count;
		Type type;
		bool normalized = false;
		uint32_t size = SizeOf(type) * count;
	};
	using VertexDataLayout = std::initializer_list<VertexBufferElement>;

	class Mesh {
	public:
		static Mesh* Create(void* vertex_data,
							uint32_t vertex_data_size,
							const VertexDataLayout& vertex_data_layout,
							uint32_t* indices,
							uint32_t index_count);
		virtual ~Mesh(void) = default;

		virtual void draw(void) const = 0;
	};

}

#endif // NEO_MESH_HPP