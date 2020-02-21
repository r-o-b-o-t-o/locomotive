#include "locomotive/components/component.h"
#include "locomotive/gameobject.h"
#include "locomotive/engine.h"

namespace Locomotive {
namespace Components {
    Component::Component() :
        enabled(true),
        parent(nullptr) {
    }

    /*void* Component::operator new(const size_t size) {
        return Engine::memoryPool().Allocate<Component>();
    }

    void Component::operator delete(void* pointer) {
        Engine::memoryPool().Deallocate<Component>((Component*)pointer);
    }*/

    bool Component::isEnabled() const {
        return this->enabled;
    }

    void Component::setEnabled(bool enabled) {
        this->enabled = enabled;
    }

    GameObject* Component::getParent() const {
        return this->parent;
    }

    void Component::setParent(GameObject* go) {
        this->parent = go;
    }
}}
