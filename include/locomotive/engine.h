#ifndef LOCOMOTIVE_ENGINE_H
#define LOCOMOTIVE_ENGINE_H

#include <chrono>
#include <iostream>
#include <vector>
#include "locomotive/locomotive.h"
#include "locomotive/scene.h"

namespace Locomotive {
	class LOCOMOTIVE_API Engine {
	public:
		void start();
		Engine();
		const double& getDeltaTime();
		const int& getFramerate();
		const int& getEffectiveFrameRate();
	private:
		int frameRate;
		double deltaTime;
		int effectiveFrameRate;
		Scene scene;
	};
}
#endif