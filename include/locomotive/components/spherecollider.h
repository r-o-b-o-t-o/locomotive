#ifndef LOCOMOTIVE_SPHERECOLLIDER_H
#define LOCOMOTIVE_SPHERECOLLIDER_H

#include "locomotive/locomotive.h"
#include "locomotive/components/component.h"

#include "glm/vec3.hpp"

namespace Locomotive {
namespace Components {
class LOCOMOTIVE_API SphereCollider : public Component {
public:
    SphereCollider();
    ~SphereCollider() = default;

    const glm::vec3& getPosition() const;
    void setPosition(glm::vec3 position);
    void setPosition(float x, float y, float z);

    float getRadius() const;
    void setRadius(float radius);

private:
    glm::vec3 offset;
    float radius;

};
}}

#endif
