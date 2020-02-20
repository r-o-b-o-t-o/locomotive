#include "locomotive/phong.h"

namespace Locomotive {
    Phong::Phong() :
            Phong(glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 0.0f, 0.0f), 32.0f) {

    }

    Phong::Phong(Phong &other) :
            Phong(other.ambient, other.diffuse, other.specular, other.shininess) {
        
    }

    Phong::Phong(const glm::vec3 &ambient, const glm::vec3 &diffuse, const glm::vec3 &specular, float shininess) :
            Material("resources/shaders/phong.vs.glsl", "resources/shaders/phong.fs.glsl") {
        this->setAmbient(ambient);
        this->setDiffuse(diffuse);
        this->setSpecular(specular);
        this->setShininess(shininess);
    }

    Phong &Phong::operator=(Phong &rhs) {
        this->setAmbient(rhs.ambient);
        this->setDiffuse(rhs.diffuse);
        this->setSpecular(rhs.specular);
        this->setShininess(rhs.shininess);
        return *this;
    }

    const glm::vec3 &Phong::getAmbient() const {
        return this->ambient;
    }

    void Phong::setAmbient(const glm::vec3 &val) {
        this->ambient = val;
        this->shader.setVec3("material.ambient", val);
    }

    const glm::vec3 &Phong::getDiffuse() const {
        return this->diffuse;
    }

    void Phong::setDiffuse(const glm::vec3 &val) {
        this->diffuse = val;
        this->shader.setVec3("material.diffuse", val);
    }

    const glm::vec3 &Phong::getSpecular() const {
        return this->specular;
    }

    void Phong::setSpecular(const glm::vec3 &val) {
        this->specular = val;
        this->shader.setVec3("material.specular", val);
    }

    float Phong::getShininess() const {
        return this->shininess;
    }

    void Phong::setShininess(float v) {
        this->shininess = v;
        this->shader.setFloat("material.shininess", v);
    }
}
