#include "locomotive/components/component.h"
#include "locomotive/gameobject.h"

namespace Locomotive {
namespace Components {

Component::Component() :
    enabled(true),
    parent(nullptr) {
}

bool Component::isEnabled() const {
    return this->enabled;
}

void Component::setEnabled(bool enabled) {
    this->enabled = enabled;
}

const GameObject* Component::getParent() const {
    return this->parent;
}

void Component::setParent(GameObject* go) {
    this->parent = go;
}
}}
