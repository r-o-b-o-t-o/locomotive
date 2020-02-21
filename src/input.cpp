#include "locomotive\input.h"
#include "GLFW/glfw3.h"

namespace Locomotive {
	Input::Input():Input(GLFW_KEY_UNKNOWN) {
		
	}
	Input::Input(int positive, int negative):positive(positive),negative(negative)
	{

	}
	int Input::update(int key)const {
		if (key == positive)return 1;
		if (key == negative)return -1;
		return 0;
	}
}