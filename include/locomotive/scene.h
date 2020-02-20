#ifndef LOCOMOTIVE_SCENE_H
#define LOCOMOTIVE_SCENE_H

#include "locomotive/locomotive.h"
#include "locomotive/gameobject.h"
#include <vector>

namespace Locomotive {
	class LOCOMOTIVE_API Scene {
		std::vector<GameObject> gameObjects;
	public:
		Scene();
		~Scene();
		void addGameObject(GameObject*);

	};
};

#endif
