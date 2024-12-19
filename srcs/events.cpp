#include "config.hpp"

float	FOV = 45.0f;
double	MOUSE_X = 0.0;
double	MOUSE_Y = 0.0;

// Resize the viewport when the window is resized
static void resize_viewport(GLFWwindow *window, int width, int height) {
	WINDOW_WIDTH = width;
	WINDOW_HEIGHT = height;
	glViewport(0, 0, width, height);
	(void)window;
}

// Update the FPS counter in the window title
static void updateFPS(GLFWwindow *window) {
	static size_t previousFPS = 0;

	if (FPS != previousFPS) {
		const string title = "42 Particle-System by DailyWind - FPS : " + to_string(FPS);
		glfwSetWindowTitle(window, title.c_str());
		previousFPS = FPS;
	}
}

// Get the normalized mouse position in MOUSE_X and MOUSE_Y
static void	getMousePos(GLFWwindow *window) {
	double	x, y;

	glfwGetCursorPos(window, &x, &y);
	MOUSE_X = 2.0f * x / WINDOW_WIDTH - 1.0f;
	MOUSE_Y = 1.0f - 2.0f * y / WINDOW_HEIGHT;
}

// Handle all keyboard & other events
void	handleEvents(GLFWwindow *window, Shader &shaders) {
	glfwPollEvents();

	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (RESIZABLE)
		glfwSetFramebufferSizeCallback(window, resize_viewport);

	updateFPS(window);
	getMousePos(window);
	
	(void)shaders; // to remove
}