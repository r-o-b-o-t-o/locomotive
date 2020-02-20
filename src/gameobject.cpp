#include "locomotive/gameobject.h"
#include "locomotive/components/component.h"
#include "locomotive/components/transform.h"

namespace Locomotive {

GameObject::GameObject() :
    enabled(true) {
    this->components.reserve(7);
}

GameObject::~GameObject() {

}

bool GameObject::isEnabled() const {
    return this->enabled;
}

void GameObject::setEnabled(bool enabled) {
    this->enabled = enabled;
}

template<>
Components::Transform* GameObject::getComponent() {
    return &this->transform;
}

void GameObject::addComponent(Components::Component* component) {
    this->components.push_back(component);
}
}
