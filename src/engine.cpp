#include "locomotive\engine.h"
#include "locomotive\threadpool.h"

namespace Locomotive {
	Engine::Engine() : deltaTime(0), frameRate(60)/*, scene()*/
	{
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
			if (frameRate != 0 && diff.count() < 1 / frameRate) continue;
			start = std::chrono::high_resolution_clock::now();
			deltaTime = diff.count();
			/*for (int j = 0; j < scene.gameObjects.size(); ++j) {
				scene.gameObjects[j].update();
			}*/
			std::cout << diff.count() << "\n";
			++i; 
			if (i == 1500)
				break;
		}
	}
}
