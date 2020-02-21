#include <chrono>

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "locomotive/engine.h"
#include "locomotive/threadpool.h"
#include "locomotive/components.h"

namespace Locomotive {
	Engine::Engine() :
			deltaTime(0.0),
			targetFramerate(60.0f),
			effectiveFrameRate(0.0f),
			scene() {
		this->arena.Initialise(4 * 1'048'576);
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

	void Engine::disableFramerateLimit() {
		this->setTargetFramerate(-1.0f);
	}

	void Engine::start() {
		/*Threadpool tp;
		tp.start(10);
		std::vector<std::future<void>> futures;
		for (auto& f : futures) {
			f.wait();
		}*/
		this->scene.init();

		std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
		std::chrono::high_resolution_clock::time_point end;
		std::chrono::duration<double> diff;
		while (true) {
			end = std::chrono::high_resolution_clock::now();
			diff = std::chrono::duration_cast<std::chrono::duration<double>>(end - start);
			if (targetFramerate > 0.000000001f && diff.count() < 1.0f / targetFramerate) {
				std::this_thread::sleep_for(std::chrono::duration<double>( (1.0f / targetFramerate) - diff.count()));
				end = std::chrono::high_resolution_clock::now();
				diff = std::chrono::duration_cast<std::chrono::duration<double>>(end - start);
			}
			start = std::chrono::high_resolution_clock::now();
			deltaTime = static_cast<float>(diff.count());
			effectiveFrameRate = 1.0f / deltaTime;

			this->scene.update(deltaTime);

			this->startRender();
			this->scene.draw(*this->scene.getCamera());
			this->endRender();

			glfwPollEvents();
		}

		this->freeResources();
	}

	void Engine::startRender() {
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void Engine::endRender() {
		//glfwSwapBuffers(this->handle);
		glFlush();
	}

	Scene &Engine::getScene() {
		return this->scene;
	}

	Arena &Engine::memoryPool() {
		return arena;
	}

	void Engine::freeResources() {
		Shader::deleteShaders();
		glfwTerminate();
	}

	Arena Engine::arena;
}
