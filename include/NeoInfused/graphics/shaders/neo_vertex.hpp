#if !defined(NEO_VERTEX_HPP)
#define NEO_VERTEX_HPP

namespace neo {
    inline const char* vertex_shader = 
        "#version 440 core\n"

        "layout (location = 0) in vec4 vertex_pos;\n"
        "layout (location = 1) in vec4 vertex_color;\n"
        "out vec4 fragment_color;\n"

        "void main(void) {\n"
            "gl_Position = vertex_pos;\n"
            "fragment_color = vertex_color;\n"
        "}\n";
} // namespace neo

#endif // NEO_VERTEX_HPP