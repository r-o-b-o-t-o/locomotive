#ifndef LOCOMOTIVE_WINDOW_H
#define LOCOMOTIVE_WINDOW_H

#include "locomotive/locomotive.h"
#include "locomotive/inputManager.h"
#include <string>

struct GLFWwindow;

namespace Locomotive {
	class LOCOMOTIVE_API Window {
	public:
		Window(const char* title, bool fullscreen = true);
		Window(std::string &title, bool fullscreen = true);
		~Window();

		void setFullscreen(bool fullscreen);
		void setDimensions(int width, int height);
		void updateAxis(int key, int action);
		void addInput(std::string const &axis, Input &&input);
		int getAxis(std::string const& axis) const;

		static Window* instance;

	private:
		static bool glfwInitialized;
		static bool gladInitialized;

		bool fullscreen;
		int x, y;
		int width, height;

		GLFWwindow* handle;
		InputManager inputmanager;

		bool initGlfw();
		bool initGlad();
	};
}

#endif
