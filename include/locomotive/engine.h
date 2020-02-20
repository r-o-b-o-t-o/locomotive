#ifndef LOCOMOTIVE_ENGINE_H
#define LOCOMOTIVE_ENGINE_H

#include <chrono>
#include <iostream>
#include <vector>
#include "locomotive/locomotive.h"
#include "locomotive/scene.h"
#include "locomotive/window.h"

namespace Locomotive {
	class Scene;

	class LOCOMOTIVE_API Engine {
	public:
		void start(Window &window);
		Engine();
		const double& getDeltaTime();
		float getTargetFramerate();
		float getEffectiveFrameRate();

	private:
		float targetFramerate;
		float effectiveFrameRate;
		float deltaTime;
		Scene scene;
	};
}
#endif