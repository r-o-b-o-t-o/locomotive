#ifndef LOCOMOTIVE_TRANSFORM_H
#define LOCOMOTIVE_TRANSFORM_H

#include "locomotive/locomotive.h"
#include "locomotive/components/component.h"

#include "glm/vec3.hpp"
#include "glm/vec4.hpp"

namespace Locomotive {
namespace Components {
class LOCOMOTIVE_API Transform : public Component {
public:
    Transform();
    ~Transform() = default;

    const glm::vec3& getPosition() const;
    void setPosition(glm::vec3 position);
    void setPosition(float x, float y, float z);

    const glm::vec3& getRotation() const;
    void setRotation(glm::vec4 rotation);
    void setRotation(float x, float y, float z, float w);

    const glm::vec3& getScale() const;
    void setScale(glm::vec3 scale);
    void setScale(float x, float y, float z);

private:
    glm::vec3 position;
    glm::vec4 rotation;
    glm::vec3 scale;

};
}}

#endif
