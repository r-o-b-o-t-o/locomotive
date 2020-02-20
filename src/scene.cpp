#include "..\include\locomotive\scene.h"

Locomotive::Scene::Scene() : gameObjects()
{
}

Locomotive::Scene::~Scene()
{
}

void Locomotive::Scene::addGameObject(GameObject* go)
{
	this->gameObjects.push_back(go);
}
