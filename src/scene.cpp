#include "locomotive/scene.h"
#include "locomotive/components/mesh.h"
#include "locomotive/components/pointlight.h"

namespace Locomotive {
		void Scene::addGameObject(GameObject* go) {
		this->gameObjects.push_back(go);
		auto mesh = go->getComponent<Components::Mesh>();
		auto cam = go->getComponent<Components::Camera>();

		if (mesh != nullptr)
			this->renderables.push_back(mesh);

		if (cam != nullptr)
			this->camera = cam;

	}

	void Scene::init() {
		auto lights = this->getComponents<Components::PointLight>();
		auto meshes = this->getComponents<Components::Mesh>();

		int nbLights = lights.size();
		for (Components::Mesh* mesh : meshes) {
			mesh->setNbPointLights(nbLights);
			for (int i = 0; i < nbLights; ++i) {
				Components::PointLight* light = lights[i];
				mesh->applyPointLight(*light, i);
			}
		}
	}

	void Scene::setAmbiantLight(glm::vec3 direction, glm::vec3 ambiant, glm::vec3 diffuse, glm::vec3 specular) {
		for (Components::Mesh* mesh : this->getComponents<Components::Mesh>()) {
			mesh->applyDirLight(direction, ambiant, diffuse, specular);
		}
	}

	std::vector<GameObject*> Scene::getGameObjects()
	{
		return this->gameObjects;
	}

	std::vector<Components::Mesh*> Scene::getRenderables()
	{
		return this->renderables;
	}

	Components::Camera* Scene::getCamera()
	{
		return this->camera;
	}

	void Scene::update() {

	}
}
