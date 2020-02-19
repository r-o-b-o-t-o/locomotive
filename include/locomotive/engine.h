#ifndef LOCOMOTIVE_ENGINE_H
#define LOCOMOTIVE_ENGINE_H

#include <chrono>
#include <iostream>
#include <vector>
#include "locomotive/locomotive.h"

namespace Locomotive {
	class LOCOMOTIVE_API Engine {
	public:
		void start();
		Engine();
	private:
		int frameRate;
		double deltaTime;
		//Scene scene;
	};
}
#endif