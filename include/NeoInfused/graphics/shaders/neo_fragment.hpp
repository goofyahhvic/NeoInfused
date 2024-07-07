#if !defined(NEO_FRAGMENT_HPP)
#define NEO_FRAGMENT_HPP

namespace neo {
    inline const char* fragment_shader =
        "#version 440 core\n"

        "in vec4 fragment_color;\n"
        "out vec4 screen_color;\n"
        
        "void main(void) {\n"
            "screen_color = fragment_color;\n"
        "}\n";
} // namespace neo

#endif // NEO_FRAGMENT_HPP