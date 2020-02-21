#include "locomotive/axis.h"
#include "GLFW/glfw3.h"

namespace Locomotive {
	Axis::Axis():value(0) {

	}
	void Axis::addInput( Input&& input) {
		inputs.push_back(std::move(input));
	}
	void Axis::update(int key,int action) {
		if (action == GLFW_PRESS)
		{
			for (Input const &input : inputs)
			{
				value += input.update(key);
			}
		}
		else
		{
			for (Input const &input : inputs)
			{
				value -= input.update(key);
			}
		}
	}
	int Axis::getValue()const {
		return value;
	}
}