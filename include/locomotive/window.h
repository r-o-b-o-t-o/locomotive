#ifndef LOCOMOTIVE_WINDOW_H
#define LOCOMOTIVE_WINDOW_H

#include "locomotive/locomotive.h"
#include <string>

struct GLFWwindow;

namespace Locomotive {
	class LOCOMOTIVE_API Window {
	public:
		Window(const char* title, bool fullscreen = true);
		Window(std::string &title, bool fullscreen = true);
		~Window();

		void startRender() const;
		void endRender() const;
		void setFullscreen(bool fullscreen);
		void setDimensions(int width, int height);

	private:
		static bool glfwInitialized;
		static bool gladInitialized;

		bool fullscreen;
		int x, y;
		int width, height;

		GLFWwindow* handle;

		bool initGlfw();
		bool initGlad();
	};
}

#endif
