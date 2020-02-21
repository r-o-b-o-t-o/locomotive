#ifndef LOCOMOTIVE_ENGINE_H
#define LOCOMOTIVE_ENGINE_H

#include "locomotive/locomotive.h"
#include "locomotive/scene.h"
#include "locomotive/window.h"
#include "locomotive/arena.h"

namespace Locomotive {
	class Scene;

	class LOCOMOTIVE_API Engine {
	public:
		void start();
		Engine();
		float getTargetFramerate();
		void setTargetFramerate(float target);
		void disableFramerateLimit();
		float getEffectiveFrameRate();
		Scene &getScene();
		static Arena &memoryPool();

	private:
		float targetFramerate;
		float effectiveFrameRate;
		float deltaTime;
		Scene scene;
		static Arena arena;

		void startRender();
		void endRender();
		void freeResources();
	};
}
#endif