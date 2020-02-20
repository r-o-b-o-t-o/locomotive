#include "locomotive/components/transform.h"

namespace Locomotive {
namespace Components {

Transform::Transform() :
    position(0, 0, 0),
    rotation(0, 0, 0, 1),
    scale(1, 1, 1) {
}

const glm::vec3& Transform::getPosition() const {
    return this->position;
}

void Transform::setPosition(glm::vec3 position) {
    this->position = position;
}

void Transform::setPosition(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

const glm::vec3& Transform::getRotation() const {
    return this->rotation;
}

void Transform::setRotation(glm::vec4 rotation) {
    this->rotation = rotation;
}

void Transform::setRotation(float x, float y, float z, float w) {
    this->rotation = glm::vec4(x, y, z, w);
}

const glm::vec3& Transform::getScale() const {
    return this->scale;
}

void Transform::setScale(glm::vec3 scale) {
    this->scale = scale;
}

void Transform::setScale(float x, float y, float z) {
    this->scale = glm::vec3(x, y, z);
}
}}