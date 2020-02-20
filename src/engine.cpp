#include <chrono>

#include "glad/glad.h"
#include "locomotive/engine.h"
#include "locomotive/threadpool.h"
#include "locomotive/components.h"

namespace Locomotive {
	Engine::Engine() :
			deltaTime(0.0),
			targetFramerate(60.0f),
			effectiveFrameRate(0.0f),
			scene() {
	}

	float Engine::getTargetFramerate() {
		return this->targetFramerate;
	}

	void Engine::setTargetFramerate(float target) {
		this->targetFramerate = target;
	}

	float Engine::getEffectiveFrameRate() {
		return this->effectiveFrameRate;
	}

	void Engine::start() {
		Threadpool tp;
		tp.start(10);
		std::vector<std::future<void>> futures;
		/*for (int j = 0; j < scene.gameObjects.size(); ++j) {
			futures.push_back(tp.queue([&scene, j] { scene.gameObjects[j].init(); }));
		}*/

		for (auto& f : futures) {
			f.wait();
		}

		int i = 0;

		std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
		std::chrono::high_resolution_clock::time_point end;
		std::chrono::duration<double> diff;
		while (true) {
			end = std::chrono::high_resolution_clock::now();
			diff = std::chrono::duration_cast<std::chrono::duration<double>>(end - start);
			if (targetFramerate != 0 && diff.count() < 1.0f / targetFramerate) {
				// TODO: sleep
				continue;
			}
			start = std::chrono::high_resolution_clock::now();
			deltaTime = static_cast<float>(diff.count());
			effectiveFrameRate = 1.0f / deltaTime;

			this->startRender();

			/*for (int j = 0; j < scene.gameObjects.size(); ++j) {
				if (scene.gameObjects[j].isEnabled())
					scene.gameObjects[j].update();
			}*/
			this->scene.update();
			
			this->endRender();

			++i; 
			if (i == 500)
				break;
		}
	}

	void Engine::startRender() {
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void Engine::endRender() {
		//glfwSwapBuffers(this->handle);
		glFlush();
	}
}
