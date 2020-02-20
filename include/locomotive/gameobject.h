#ifndef LOCOMOTIVE_GAMEOBJECT_H
#define LOCOMOTIVE_GAMEOBJECT_H

#include "locomotive/locomotive.h"
#include "locomotive/components/component.h"
#include "locomotive/components/transform.h"

#include <vector>

namespace Locomotive {
class LOCOMOTIVE_API GameObject {
public:
    GameObject();
    ~GameObject();

    bool isEnabled() const;
    void setEnabled(bool enabled);

    template<class C>
    C* getComponent() {
        for (Components::Component* component : components) {
            C* cast = dynamic_cast<C*>(component);
            if (cast) {
                return cast;
            }
        }

        return nullptr;
    }
    void addComponent(Components::Component* component);

private:
    bool enabled;
    Components::Transform transform;
    std::vector<Components::Component*> components;

};
}

#endif
