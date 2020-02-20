#ifndef LOCOMOTIVE_ENGINE_H
#define LOCOMOTIVE_ENGINE_H

#include "locomotive/locomotive.h"
#include "locomotive/scene.h"
#include "locomotive/window.h"

namespace Locomotive {
	class Scene;

	class LOCOMOTIVE_API Engine {
	public:
		void start();
		Engine();
		float getTargetFramerate();
		void setTargetFramerate(float target);
		float getEffectiveFrameRate();

	private:
		float targetFramerate;
		float effectiveFrameRate;
		float deltaTime;
		Scene scene;

		void startRender();
		void endRender();
	};
}
#endif