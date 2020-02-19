#include "glad/glad.h"
#include "locomotive/mesh.h"

namespace Locomotive {
    Mesh::Mesh(const std::vector<glm::vec3> &vertices) :
            vertices(vertices) {
        glGenVertexArrays(1, &this->vao);
        glGenBuffers(1, &this->vbo);

        glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), this->vertices.data(), GL_STATIC_DRAW);

        glBindVertexArray(this->vao);

        // Position attribute
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        // Normal attribute
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
    }

    void Mesh::draw(Material &mat) const {
        mat.getShader().use();
        glBindVertexArray(this->vao);
        glDrawArrays(GL_TRIANGLES, 0, static_cast<GLsizei>(this->vertices.size() / 2)); // / 2 = position and normal attribute
        glBindVertexArray(0);
    }
}
