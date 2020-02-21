#ifndef LOCOMOTIVE_COMPONENTS_TRANSFORM_H
#define LOCOMOTIVE_COMPONENTS_TRANSFORM_H

#include "locomotive/locomotive.h"
#include "locomotive/components/component.h"

#include "glm/vec3.hpp"
#include "glm/mat4x4.hpp"
#include "glm/gtc/quaternion.hpp"

namespace Locomotive {
namespace Components {
    class LOCOMOTIVE_API Transform : public Component {
    public:
        Transform();
        ~Transform() = default;

        const glm::vec3& getPosition() const;
        void setPosition(glm::vec3 position);
        void setPosition(float x, float y, float z);
        void translate(glm::vec3 delta);
        void translate(float x, float y, float z);

        const glm::quat& getRotation() const;
        glm::vec3 getRotationEulerAngles() const;
        void setRotation(glm::quat rotation);
        void setRotation(float x, float y, float z, float w);
        void setRotation(glm::vec3);
        void setRotation(float x, float y, float z);

        void rotate(glm::vec3 rotation);
        void rotate(float x, float y, float z);
        void rotate(float angle, glm::vec3 axis);

        const glm::vec3& getScale() const;
        void setScale(glm::vec3 scale);
        void setScale(float x, float y, float z);
        void setScale(float scale);

        glm::mat4x4 getTransformMatrix() const;
        glm::vec3 right() const;
        glm::vec3 up() const;
        glm::vec3 forward() const;
        void lookAt(float x, float y, float z);
        void lookAt(glm::vec3 target);
        void lookAt(const Transform &target);

    private:
        glm::vec3 position;
        glm::quat rotation;
        glm::vec3 scale;
    };
}}

#endif
