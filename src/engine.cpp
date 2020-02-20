#include "..\include\locomotive\engine.h"
namespace Locomotive {
	Engine::Engine() : deltaTime(0), frameRate(60)/*, scene()*/
	{
	}

	void Engine::start() {
		/*for (int j = 0; j < scene.gameObjects.size(); ++j) {
			scene.gameObjects[j].init();
		}*/
		int i = 0;

		std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
		std::chrono::high_resolution_clock::time_point end;
		std::chrono::duration<double> diff;
		while (true) {

			end = std::chrono::high_resolution_clock::now();
			diff = std::chrono::duration_cast<std::chrono::duration<double>>(end - start);
			start = std::chrono::high_resolution_clock::now();
			if (frameRate != 0 && diff.count() < 1 / frameRate) continue;
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
