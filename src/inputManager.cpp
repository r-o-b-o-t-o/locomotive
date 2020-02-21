#include "locomotive/inputManager.h"
#include "GLFW/glfw3.h"

namespace Locomotive {
	InputManager::InputManager()
	{

	}

	void InputManager::addInput(std::string axis, Input&& input) {
		this->axis[axis].addInput(std::move(input));
	}
	void InputManager::update(int key, int action) {
		if (action == GLFW_REPEAT)return;
		for (auto &axis : this->axis)
		{
			axis.second.update(key, action);
		}
	}
	int InputManager::getAxis(std::string axis)const {
		auto r = this->axis.find(axis);
		if (r == this->axis.end())return 0;
		return r->second.getValue();
	}
}
