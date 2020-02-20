#ifndef LOCOMOTIVE_SCENE_H
#define LOCOMOTIVE_SCENE_H

#include "locomotive/locomotive.h"
#include "locomotive/gameobject.h"
#include "locomotive/components/mesh.h"
#include "locomotive/components/camera.h"
#include <vector>

namespace Locomotive {
	class LOCOMOTIVE_API Scene {
	public:

		void addGameObject(GameObject*);
		void setAmbiantLight(glm::vec3 direction, glm::vec3 ambiant, glm::vec3 diffuse, glm::vec3 specular);

		std::vector<GameObject*> getGameObjects();
		std::vector<Components::Mesh*> getRenderables();
		Components::Camera* getCamera();

	private:
		std::vector<GameObject*> gameObjects;
		std::vector<Components::Mesh*> renderables;
		Components::Camera* camera;

		void init();
		void update();
		
		template<class C>
		std::vector<C*> getComponents() {
			std::vector<C*> components;
			for (GameObject* go : this->gameObjects) {
				if (C* component = go->getComponent<C>()) {
					components.push_back(component);
				}
			}
			return components;
		}
	};
};

#endif
