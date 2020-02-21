#include "locomotive/gameobject.h"
#include "locomotive/engine.h"

namespace Locomotive {
    GameObject::GameObject() :
            enabled(true) {
        this->components.reserve(7);
    }

    GameObject::~GameObject() {

    }

    void* GameObject::operator new(const size_t size) {
        return Engine::memoryPool().Allocate<GameObject>();
    }

    void GameObject::operator delete(void* pointer) {
        Engine::memoryPool().Deallocate<GameObject>((GameObject*)pointer);
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
        component->setParent(this);
        this->components.push_back(component);
    }

    Components::Transform& GameObject::getTransform() {
        return this->transform;
    }
}
