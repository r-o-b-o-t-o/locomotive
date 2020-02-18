#include "GLFW/glfw3.h"
#include "locomotive/window.h"

namespace Locomotive {
	bool Window::glfwInitialized = false;

	Window::Window(const char* title) {
		if (!glfwInitialized) {
			glfwInit();
			glfwInitialized = true;
		}

		GLFWmonitor* monitor = glfwGetPrimaryMonitor();
		const GLFWvidmode* mode = glfwGetVideoMode(monitor);
		glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
		glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);
		this->handle = glfwCreateWindow(mode->width, mode->height, title, monitor, nullptr);
	}

	Window::Window(std::string &title)
			: Window::Window(title.c_str()) {
	}

	Window::~Window() {
		glfwDestroyWindow(this->handle);
	}

	void Window::SetFullscreen(bool fullscreen) const {
		GLFWmonitor* monitor = glfwGetPrimaryMonitor();

		if (fullscreen) {
			// Backup position and size
			//glfwGetWindowPos(this->handle, &x, &y);
			//glfwGetWindowSize(this->handle, &width, &height);

			const GLFWvidmode* mode = glfwGetVideoMode(monitor);
			glfwSetWindowMonitor(this->handle, monitor, 0, 0, mode->width, mode->height, 0);
		} else {
			// Restore last window size and position
			//glfwSetWindowMonitor(this->handle, nullptr, x, y, width, height, 0);
		}
	}
}
