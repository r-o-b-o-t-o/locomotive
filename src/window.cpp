#include "glad/glad.h" // Must be included before GLFW!
#include "GLFW/glfw3.h"
#include "locomotive/window.h"

#include <iostream>

namespace Locomotive {
	bool Window::glfwInitialized = false;
	bool Window::gladInitialized = false;

	Window::Window(const char* title, bool fullscreen) {
		if (!glfwInitialized) {
			if (!this->initGlfw()) {
				return;
			}
		}

		GLFWmonitor* monitor = glfwGetPrimaryMonitor();
		const GLFWvidmode* mode = glfwGetVideoMode(monitor);

		this->width = mode->width;
		this->height = mode->height;
		if (!fullscreen) {
			this->width /= 2;
			this->height /= 2;
		}
		this->x = (mode->width - this->width) / 2;
		this->y = (mode->height - this->height) / 2;
		this->fullscreen = fullscreen;

		glfwWindowHint(GLFW_DOUBLEBUFFER, GL_FALSE);
		if (fullscreen) {
			this->handle = glfwCreateWindow(this->width, this->height, title, monitor, nullptr);
		} else {
			this->handle = glfwCreateWindow(this->width, this->height, title, nullptr, nullptr);
			glfwSetWindowPos(this->handle, this->x, this->y);
		}
		if (this->handle == nullptr) {
			std::cerr << "Failed to create GLFW window" << std::endl;
			glfwTerminate();
			return;
		}
		glfwMakeContextCurrent(this->handle);

		if (!gladInitialized) {
			if (!initGlad()) {
				return;
			}
		}

		glViewport(0, 0, this->width, this->height);
	}

	Window::Window(std::string &title, bool fullscreen)
			: Window::Window(title.c_str(), fullscreen) {
	}

	Window::~Window() {
		// TODO: call glfwTerminate() when there are no windows left
		glfwDestroyWindow(this->handle);
	}

	bool Window::initGlfw() {
		if (glfwInit() == GLFW_FALSE) {
			std::cerr << "Failed to initialize GLFW" << std::endl;
			return false;
		}
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

		glfwInitialized = true;
		return true;
	}

	bool Window::initGlad() {
		int res = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		if (!res) {
			std::cerr << "Failed to initialize GLAD (" << res << ")" << std::endl;
			return false;
		}

		glEnable(GL_DEPTH_TEST);

		gladInitialized = true;
		return true;
	}

	void Window::startRender() const {
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void Window::endRender() const {
		//glfwSwapBuffers(this->handle);
		glFlush();
	}

	void Window::setFullscreen(bool fullscreen) {
		GLFWmonitor* monitor = glfwGetPrimaryMonitor();

		if (fullscreen) {
			// Backup position and size
			glfwGetWindowPos(this->handle, &this->x, &this->y);
			glfwGetWindowSize(this->handle, &this->width, &this->height);

			const GLFWvidmode* mode = glfwGetVideoMode(monitor);
			glfwSetWindowMonitor(this->handle, monitor, 0, 0, mode->width, mode->height, -1);
			glViewport(0, 0, mode->width, mode->height);
		} else {
			// Restore last window size and position
			glfwSetWindowMonitor(this->handle, nullptr, this->x, this->y, this->width, this->height, -1);
			glfwSetWindowAttrib(this->handle, GLFW_DECORATED, GLFW_TRUE);
			glViewport(0, 0, this->width, this->height);
		}

		this->fullscreen = fullscreen;
	}

	void Window::setDimensions(int width, int height) {
		this->width = width;
		this->height = height;

		if (!this->fullscreen) {
			glfwSetWindowMonitor(this->handle, nullptr, this->x, this->y, this->width, this->height, -1);
			glViewport(0, 0, this->width, this->height);
		}
	}
}
