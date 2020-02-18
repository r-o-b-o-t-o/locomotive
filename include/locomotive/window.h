#ifndef LOCOMOTIVE_WINDOW_H
#define LOCOMOTIVE_WINDOW_H

#include "locomotive/locomotive.h"
#include <string>

struct GLFWwindow;

namespace Locomotive {
	class LOCOMOTIVE_API Window {
	public:
		Window(const char* title);
		Window(std::string &title);
		~Window();

		void SetFullscreen(bool fullscreen) const;

	private:
		static bool glfwInitialized;

		GLFWwindow* handle;
	};
}

#endif