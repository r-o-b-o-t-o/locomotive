#include "locomotive/scene.h"
#include "locomotive/components/pointlight.h"

namespace Locomotive {
	Scene::Scene() {
		activeScene = this;
	}

	void Scene::addGameObject(GameObject* go) {
		this->gameObjects.push_back(go);

		auto r = go->getComponents<Components::Mesh>();
		this->renderables.insert(this->renderables.end(), r.begin(), r.end());

		auto b = go->getComponents<Components::Behaviour>();
		this->behaviours.insert(this->behaviours.end(), b.begin(), b.end());

		if (auto cam = go->getComponent<Components::Camera>()) {
			this->camera = cam;
		}
	}

	void Scene::init() {
		auto lights = this->getComponents<Components::PointLight>();
		auto meshes = this->getComponents<Components::Mesh>();

		int nbLights = lights.size();
		for (Components::Mesh* mesh : meshes) {
			if (!mesh->isEnabled() || !mesh->getParent()->isEnabled()) {
				continue;
			}
			mesh->setNbPointLights(nbLights);
			for (int i = 0; i < nbLights; ++i) {
				Components::PointLight* light = lights[i];
				if (light->isEnabled() && light->getParent()->isEnabled()) {
					mesh->applyPointLight(*light, i);
				}
			}
		}

		for (Components::Behaviour* b : this->behaviours) {
			if (b->isEnabled() && b->getParent()->isEnabled()) {
				b->start();
			}
		}
	}

	void Scene::draw(Components::Camera &cam) {
		for (auto m : renderables) {
			if (m->isEnabled() && m->getParent()->isEnabled()) {
				m->draw(cam);
			}
		}
	}

	void Scene::setAmbiantLight(glm::vec3 direction, glm::vec3 ambiant, glm::vec3 diffuse, glm::vec3 specular) {
		for (Components::Mesh* mesh : this->getComponents<Components::Mesh>()) {
			mesh->applyDirLight(direction, ambiant, diffuse, specular);
		}
	}

	Components::Camera* Scene::getCamera() {
		return this->camera;
	}

	void Scene::update(float deltaTime) {
		for (Components::Behaviour* b : this->behaviours) {
			if (b->isEnabled()) {
				b->update(deltaTime);
			}
		}
	}

	Scene* Scene::activeScene = nullptr;
}
