#include "locomotive/components/transform.h"
#include "glm/ext/matrix_transform.hpp"
#include <glm/gtx/quaternion.hpp>

#include <iostream>

const float deg2rad = (glm::pi<float>() * 2.0f) / 360.0f;
const float rad2deg = 360.0f / (glm::pi<float>() * 2.0f);

namespace Locomotive {
namespace Components {
    Transform::Transform() :
            position(0.0f, 0.0f, 0.0f),
            scale(1.0f, 1.0f, 1.0f) {
        this->setRotation(0.0f, 0.0f, 0.0f);
    }

    const glm::vec3& Transform::getPosition() const {
        return this->position;
    }

    void Transform::setPosition(glm::vec3 position) {
        this->position = position;
    }

    void Transform::setPosition(float x, float y, float z) {
        this->setPosition(glm::vec3(x, y, z));
    }

    void Transform::translate(glm::vec3 delta) {
        this->setPosition(this->getPosition() + delta);
    }

    void Transform::translate(float x, float y, float z) {
        this->translate(glm::vec3(x, y, z));
    }

    const glm::quat& Transform::getRotation() const {
        return this->rotation;
    }

    glm::vec3 Transform::getRotationEulerAngles() const {
        return glm::eulerAngles(this->rotation) * rad2deg;
    }

    void Transform::setRotation(glm::quat rotation) {
        this->rotation = rotation;
    }

    void Transform::setRotation(float x, float y, float z, float w) {
        this->setRotation(glm::quat(x, y, z, w));
    }

    void Transform::setRotation(glm::vec3 euler) {
        this->rotation = glm::quat(euler * deg2rad);
    }

    void Transform::setRotation(float x, float y, float z) {
        this->setRotation(glm::vec3(x, y, z));
    }

    const glm::vec3& Transform::getScale() const {
        return this->scale;
    }

    void Transform::setScale(glm::vec3 scale) {
        this->scale = scale;
    }

    void Transform::setScale(float x, float y, float z) {
        this->setScale(glm::vec3(x, y, z));
    }

    void Transform::setScale(float scale) {
        this->setScale(scale, scale, scale);
    }

    void Transform::rotate(glm::vec3 rotation) {
        this->rotation *= glm::quat(rotation * deg2rad);
    }

    void Transform::rotate(float x, float y, float z) {
        this->rotate(glm::vec3(x, y, z));
    }

    void Transform::rotate(float angle, glm::vec3 axis) {
        this->rotate(angle * axis);
    }

    glm::mat4x4 Transform::getTransformMatrix() const {
        glm::mat4x4 mat(1.0f);
        mat = glm::translate(mat, this->position);
        mat *= glm::toMat4(this->rotation);
        mat = glm::scale(mat, this->scale);
        return mat;
    }

    glm::vec3 Transform::right() const {
        return this->rotation * glm::vec3(1.0f, 0.0f, 0.0f);
    }

    glm::vec3 Transform::up() const {
        return this->rotation * glm::vec3(0.0f, 1.0f, 0.0f);
    }

    glm::vec3 Transform::forward() const {
        return this->rotation * glm::vec3(0.0f, 0.0f, -1.0f);
    }

    void Transform::lookAt(float x, float y, float z) {
        this->lookAt(glm::vec3(x, y, z));
    }

    void Transform::lookAt(glm::vec3 target) {
        glm::vec3  direction = target - this->position;
        float directionLength = glm::length(direction);

        // Check if the direction is valid; Also deals with NaN
        if (!(directionLength > 0.0001f)) {
            this->rotation = glm::quat(1, 0, 0, 0); // Just return identity
        }

        // Normalize direction
        direction /= directionLength;

        this->rotation = glm::quatLookAt(direction, this->up());
    }

    void Transform::lookAt(const Transform &target) {
        this->lookAt(target.getPosition());
    }
}}
