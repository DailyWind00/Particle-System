#include "config.hpp"
#include <cstdlib>
#include <unistd.h>

int WINDOW_WIDTH = 1080 * 0.80f;
int WINDOW_HEIGHT = 1080 * 0.80f;

static void configureGraphicsBackend() {
#if defined(__linux__) || defined(__unix__)
	if (access("/proc/driver/nvidia", F_OK) == 0) {
		if (getenv("__NV_PRIME_RENDER_OFFLOAD") == nullptr)
			setenv("__NV_PRIME_RENDER_OFFLOAD", "1", 0);
		if (getenv("__GLX_VENDOR_LIBRARY_NAME") == nullptr)
			setenv("__GLX_VENDOR_LIBRARY_NAME", "nvidia", 0);
	}
#endif
}

// Initialize GLFW and create a window
GLFWwindow	*CreateWindow() {
	GLFWwindow	*window;

	configureGraphicsBackend();

	if (!glfwInit()) {
		cerr << BRed << "Failed to initialize GLFW" << ResetColor << '\n';
		exit(EXIT_FAILURE);
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4); // OpenGL 4.5
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // Mac-os compatibility
	glfwWindowHint(GLFW_SAMPLES, 4);
	if (!RESIZABLE)
		glfwWindowHint(GLFW_RESIZABLE, false);

	printVerbose("GLFW initialized");

	const string title = "42 Particle-System by DailyWind";
	window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, title.c_str(), nullptr, nullptr);
	if (!window) {
		glfwTerminate();
		throw runtime_error("Failed to create window");
	}
	printVerbose("Window \"" + title + "\" created");

	glfwMakeContextCurrent(window);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		glfwTerminate();
		throw runtime_error("Failed to initialize GLAD");
	}
	printVerbose("GLAD initialized");

	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

	return window;
}

// Destroy the window and terminate GLFW
// Should only be called if CreateWindow was successful
void	DestroyWindow(GLFWwindow *window) {
	if (!window)
		return;
	glfwDestroyWindow(window);
	glfwTerminate();
	printVerbose("Window destroyed");
}

