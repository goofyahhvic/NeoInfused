#if !defined(INF_SHADERS_SRC_HPP)
#define INF_SHADERS_SRC_HPP

#include "inf_core.hpp"

namespace inf::Shaders {
	inline const char* default_vertex = R"(
		#version 450 core
		
        layout (location = 0) in vec3 a_VertexPosition;
        out vec4 o_VertexColor;

        void main(void) {
            gl_Position = vec4(a_VertexPosition, 1.0);
            o_VertexColor = vec4(a_VertexPosition, 1.0);
        }
	)";


    inline const char* default_fragment = R"(
        #version 450 core

        in vec4 o_VertexColor;
        out vec4 o_ScreenColor;

        void main(void) {
            o_ScreenColor = o_VertexColor;
        }
    )";
}

#endif // INF_SHADERS_SRC_HPP