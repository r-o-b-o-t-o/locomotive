#ifndef LOCOMOTIVE_INPUTMANAGER_H
#define LOCOMOTIVE_INPUTMANAGER_H

#include "locomotive\locomotive.h"
#include "locomotive\axis.h"
#include <map>

struct GLFWwindow;

namespace Locomotive {
	class LOCOMOTIVE_API InputManager {
	public:
		InputManager();
		void addInput(std::string axis,  Input&& input);
		void update(int key, int action);
		int getAxis(std::string axis)const;
	private:
		std::map<std::string, Axis> axis;
	};
}


#endif