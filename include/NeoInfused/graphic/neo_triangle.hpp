#if !defined(NEO_TRIANGLE_HPP)
#define NEO_TRIANGLE_HPP

#include "neo_graphic.hpp"

namespace neo {
    struct Vertex {
        glm::vec3 position;
        glm::vec4 color;
    };

    class Triangle : public Graphic {
    public:
        Triangle(Vertex vertices[3]);
        ~Triangle(void);
    public:
        void draw(void) override;
        void set_vertex(const Vertex& vertex, uint8_t index);
        void set_position(const glm::vec3& position, uint8_t index);
        void set_color(const glm::vec4& color, uint8_t index);

    private:
        uint32_t m_VertexBuffer, m_VertexArray;
    };
} // namespace neo

#endif // NEO_TRIANGLE_HPP