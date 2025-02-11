#include "glad/glad.h"
#include "locomotive/components/mesh.h"
#include "OBJ_Loader/OBJ_Loader.h"

glm::vec3 loaderVec3ToGlm(const objl::Vector3 &vec) {
    return glm::vec3(vec.X, vec.Y, vec.Z);
}

namespace Locomotive {
namespace Components {
    Mesh::Mesh(const std::string &modelPath) :
            instancesVbo(0),
            nbInstances(0) {
        objl::Loader loader;
        bool load = loader.LoadFile(modelPath);

        if (load) {
            this->shapes.reserve(loader.LoadedMeshes.size());

            for (int i = 0; i < loader.LoadedMeshes.size(); i++) {
                std::vector<glm::vec3> vertices;
                std::vector<unsigned int> indices;

                objl::Mesh &curMesh = loader.LoadedMeshes[i];

                for (int j = 0; j < curMesh.Vertices.size(); j++) {
                    vertices.push_back(loaderVec3ToGlm(curMesh.Vertices[j].Position));
                    vertices.push_back(loaderVec3ToGlm(curMesh.Vertices[j].Normal));
                }

                for (int j = 0; j < curMesh.Indices.size(); j += 3) {
                    indices.push_back(curMesh.Indices[j]);
                    indices.push_back(curMesh.Indices[j + 1]);
                    indices.push_back(curMesh.Indices[j + 2]);
                }

                Shape &shape = this->shapes.emplace_back(vertices, indices);
                shape.material.setAmbient(loaderVec3ToGlm(curMesh.MeshMaterial.Ka));
                shape.material.setDiffuse(loaderVec3ToGlm(curMesh.MeshMaterial.Kd));
                shape.material.setSpecular(loaderVec3ToGlm(curMesh.MeshMaterial.Ks));
                shape.material.setShininess(curMesh.MeshMaterial.Ns);
            }
        }
    }

    Mesh::~Mesh() {
        glDeleteBuffers(1, &this->instancesVbo);
    }

    Mesh::Mesh(const Mesh &other) {
        *this = other;
    }

    Mesh &Mesh::operator=(const Mesh &rhs) {
        if (this != &rhs) {
            this->~Mesh();
            this->shapes = rhs.shapes;
            this->nbInstances = rhs.nbInstances;
            this->instancesVbo = rhs.instancesVbo;
        }
        return *this;
    }

    void Mesh::draw(Camera &cam) {
        for (Shape &shape : this->shapes) {
            Shader &shader = shape.material.getShader();

            shader.setMat4("projection", cam.getProjectionMatrix());
            shader.setMat4("view", cam.getViewMatrix());
            shader.setVec3("viewPos", cam.getParent()->getTransform().getPosition());
            shader.setMat4("model", this->getParent()->getTransform().getTransformMatrix());

            shader.use();
            glBindVertexArray(shape.vao);
            glBindBuffer(GL_ARRAY_BUFFER, shape.vbo);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, shape.ibo);
            if (this->nbInstances > 0 && this->instancesVbo != 0) {
                glDrawElementsInstanced(GL_TRIANGLES, static_cast<GLsizei>(shape.indices.size()), GL_UNSIGNED_INT, (void*)0, this->nbInstances);
            } else {
                glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(shape.indices.size()), GL_UNSIGNED_INT, (void*)0);
            }
        }
    }

    void Mesh::setInstances(std::vector<glm::mat4> &instances) {
        this->nbInstances = instances.size();
        if (nbInstances == 0) {
            return;
        }

        GLsizei vec4Size = sizeof(glm::vec4);

        glGenBuffers(1, &this->instancesVbo);
        glBindBuffer(GL_ARRAY_BUFFER, this->instancesVbo);
        glBufferData(GL_ARRAY_BUFFER, this->nbInstances * sizeof(glm::mat4), instances.data(), GL_STATIC_DRAW);

        for (Shape &shape : this->shapes) {
            Shader &shader = shape.material.getShader();
            shader.setBool("instanced", true);

            glBindVertexArray(shape.vao);
            // Set attribute pointers for matrix (4 times vec4)
            glEnableVertexAttribArray(2);
            glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void*)0);
            glEnableVertexAttribArray(3);
            glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void*)(vec4Size));
            glEnableVertexAttribArray(4);
            glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void*)(2 * vec4Size));
            glEnableVertexAttribArray(5);
            glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void*)(3 * vec4Size));

            glVertexAttribDivisor(2, 1);
            glVertexAttribDivisor(3, 1);
            glVertexAttribDivisor(4, 1);
            glVertexAttribDivisor(5, 1);
            glBindVertexArray(0);
        }
    }

    void Mesh::applyPointLight(PointLight &light, int idx) {
        for (Shape &shape : this->shapes) {
            Shader &shader = shape.material.getShader();
            std::string prop = "pointLights[" + std::to_string(idx) + "]";
            shader.setVec3(prop + ".position", light.getParent()->getTransform().getPosition());
            shader.setVec3(prop + ".ambient", light.ambiant);
            shader.setVec3(prop + ".diffuse", light.diffuse);
            shader.setVec3(prop + ".specular", light.specular);
            shader.setFloat(prop + ".constant", light.constant);
            shader.setFloat(prop + ".linear", light.linear);
            shader.setFloat(prop + ".quadratic", light.quadratic);
        }
    }

    void Mesh::applyDirLight(glm::vec3 direction, glm::vec3 ambiant, glm::vec3 diffuse, glm::vec3 specular) {
        for (Shape &shape : this->shapes) {
            Shader &shader = shape.material.getShader();
            std::string prop = "dirLight";
            shader.setVec3(prop + ".direction", direction);
            shader.setVec3(prop + ".ambiant", ambiant);
            shader.setVec3(prop + ".diffuse", diffuse);
            shader.setVec3(prop + ".specular", specular);
        }
    }

    void Mesh::setNbPointLights(int n) {
        for (Shape &shape : this->shapes) {
            shape.material.getShader().setInt("nbPointLights", n);
        }
    }

    std::vector<Mesh::Shape> &Mesh::getShapes() {
        return this->shapes;
    }

    Mesh::Shape::Shape(std::vector<glm::vec3> vertices, std::vector<unsigned int> indices) :
            vao(0),
            vbo(0),
            ibo(0),
            vertices(vertices),
            indices(indices) {
        this->init();
    }

    Mesh::Shape::Shape(const Shape &other) :
            Shape(other.vertices, other.indices) {

    }

    Mesh::Shape::~Shape() {
        glDeleteVertexArrays(1, &this->vao);
        glDeleteBuffers(1, &this->vbo);
        glDeleteBuffers(1, &this->ibo);
    }

    Mesh::Shape& Mesh::Shape::operator=(const Shape &rhs) {
        if (this != &rhs) {
            this->~Shape();
            this->vertices = rhs.vertices;
            this->indices = rhs.indices;
            this->init();
        }
        return *this;
    }

    void Mesh::Shape::init() {
        glGenVertexArrays(1, &this->vao);
        glBindVertexArray(this->vao);

        glGenBuffers(1, &this->vbo);
        glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
        glBufferData(GL_ARRAY_BUFFER, this->vertices.size() * sizeof(glm::vec3), this->vertices.data(), GL_STATIC_DRAW);

        glGenBuffers(1, &this->ibo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ibo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indices.size() * sizeof(unsigned int), this->indices.data(), GL_STATIC_DRAW);

        // Position attribute
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        // Normal attribute
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
    }
}
}
