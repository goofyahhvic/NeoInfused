#if !defined(NEO_SHADERS_HPP)
#define NEO_SHADERS_HPP

namespace neo {
	namespace Shaders {
		inline const char* default_vertex =
            "#version 440 core\n"

            "layout (location = 0) in vec4 vertex_pos;\n"
            "layout (location = 1) in vec4 vertex_color;\n"
            "out vec4 fragment_color;\n"

            "void main(void) {\n"
                "gl_Position = vertex_pos;\n"
                "fragment_color = vertex_color;\n"
            "}\n";

		inline const char* default_fragment =
            "#version 440 core\n"

            "in vec4 fragment_color;\n"
            "out vec4 screen_color;\n"

            "void main(void) {\n"
                "screen_color = fragment_color;\n"
            "}\n";
	};
}

#endif // NEO_SHADERS_HPP