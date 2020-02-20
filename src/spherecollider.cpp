#include "locomotive/components/spherecollider.h"

namespace Locomotive {
namespace Components {

SphereCollider::SphereCollider() :
    offset(0, 0, 0),
    radius(1.0f) {
}

const glm::vec3& SphereCollider::getPosition() const {
    return this->offset;
}

void SphereCollider::setPosition(glm::vec3 position) {
    this->offset = position;
}

void SphereCollider::setPosition(float x, float y, float z) {
    this->offset = glm::vec3(x, y, z);
}

float SphereCollider::getRadius() const {
    return this->radius;
}

void SphereCollider::setRadius(float radius) {
    this->radius = radius;
}
}}

