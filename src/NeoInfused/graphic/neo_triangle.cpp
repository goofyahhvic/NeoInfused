#include "neo_pch.hpp"
#include "NeoInfused/graphic/neo_triangle.hpp"

namespace neo {
    Triangle::Triangle(Vertex vertices[3]) {
        glGenVertexArrays(1, &m_VertexArray);
        glBindVertexArray(m_VertexArray);

        glGenBuffers(1, &m_VertexBuffer);
        glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);
        glBufferData(GL_ARRAY_BUFFER, 3 * sizeof(Vertex), vertices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 28, (void*)0);
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 28, (void*)12);
        glEnableVertexAttribArray(1);
    }
    Triangle::~Triangle(void) {
        glDeleteVertexArrays(1, &m_VertexArray);
        glDeleteBuffers(1, &m_VertexBuffer);
    }

    void Triangle::draw(void) {
        glBindVertexArray(m_VertexArray);
        glDrawArrays(GL_TRIANGLES, 0, 3);
    }

    void Triangle::set_vertex(const Vertex& vertex, uint8_t index) {
        glBindVertexArray(m_VertexArray);
        glBufferSubData(GL_ARRAY_BUFFER, index * sizeof(Vertex), sizeof(Vertex), &vertex);
    }
    void Triangle::set_position(const glm::vec3& pos, uint8_t index) {
        glBindVertexArray(m_VertexArray);
        glBufferSubData(GL_ARRAY_BUFFER, index * sizeof(Vertex), sizeof(glm::vec3), &pos);
    }
    void Triangle::set_color(const glm::vec4& color, uint8_t index) {
        glBindVertexArray(m_VertexArray);
        glBufferSubData(GL_ARRAY_BUFFER, index * sizeof(Vertex) + 12, sizeof(glm::vec4), &color);
    }
} // namespace neo
