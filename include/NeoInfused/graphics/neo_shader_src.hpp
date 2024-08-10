#if !defined(NEO_SHADER_SRC_HPP)
#define NEO_SHADER_SRC_HPP

#include "neo_context.hpp"

namespace neo::Shaders {
	inline const char* default_vertex = R"(
        #version 460 core

        layout (location = 0) in vec3 a_VertexPosition;
        layout (location = 1) in vec4 a_VertexColor;
        out vec4 o_VertexColor;

        void main(void) {
            gl_Position = vec4(a_VertexPosition, 1.0);
            o_VertexColor = a_VertexColor;
        }
    )";

	inline const char* default_fragment = R"(
        #version 460 core

        in vec4 o_VertexColor;
        out vec4 o_ScreenColor;

        void main(void) {
            o_ScreenColor = o_VertexColor;
        }
    )";

} // namespace neo::Shaders

#endif // NEO_SHADER_SRC_HPP