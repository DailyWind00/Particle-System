#include "config.hpp"

float	FOV = 45.0f;

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

// Handle all keyboard & other events
void	handleEvents(GLFWwindow *window, Shader &shaders) {
	glfwPollEvents();

	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (RESIZABLE)
		glfwSetFramebufferSizeCallback(window, resize_viewport);

	updateFPS(window);
	
	(void)shaders; // to remove
}