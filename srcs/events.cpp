#include "config.hpp"
#include "ParticleSystem.hpp"

float	FOV = 45.0f;
float	MOUSE_X = 0.0;
float	MOUSE_Y = 0.0;

// Resize the viewport when the window is resized
static void resize_viewport(GLFWwindow *window, int width, int height) {
	WINDOW_WIDTH = width;
	WINDOW_HEIGHT = height;
	glViewport(0, 0, width, height);
	(void)window;
}

// Toggle fullscreen mode
static void setFullscreen(GLFWwindow *window) {
	static bool fullscreenKeyPressed = false;

	if (glfwGetKey(window, GLFW_KEY_F11) == GLFW_PRESS) {
		if (fullscreenKeyPressed)
			return;

		static bool fullscreen = true;
		static int x, y, width, height;

		if (fullscreen) {
			GLFWmonitor* monitor = glfwGetPrimaryMonitor();
			const GLFWvidmode* mode = glfwGetVideoMode(monitor);

			// Save the window position and size
			glfwGetWindowPos(window, &x, &y);
			glfwGetWindowSize(window, &width, &height);

			glfwSetWindowMonitor(window, monitor, 0, 0, mode->width, mode->height, mode->refreshRate);
			printVerbose("Fullscreen mode");
		}
		else {
			glfwSetWindowMonitor(window, nullptr, x, y, width, height, 0);
			printVerbose("Windowed mode");
		}

		fullscreen = !fullscreen;
		fullscreenKeyPressed = true;
	}
	else
		fullscreenKeyPressed = false;
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

static void changeParticlesSize(GLFWwindow *window) {
	static bool sizeKeyPressed = false;

	if (glfwGetKey(window, GLFW_KEY_KP_ADD) == GLFW_PRESS) {
		if (sizeKeyPressed)
			return;

		PARTICLE_SIZE += 1;
		glPointSize(PARTICLE_SIZE);
		printVerbose("Particles size : " + to_string(PARTICLE_SIZE));
		sizeKeyPressed = true;
	}
	else if (glfwGetKey(window, GLFW_KEY_KP_SUBTRACT) == GLFW_PRESS && PARTICLE_SIZE > 1) {
		if (sizeKeyPressed)
			return;

		PARTICLE_SIZE -= 1;
		glPointSize(PARTICLE_SIZE);
		printVerbose("Particles size : " + to_string(PARTICLE_SIZE));
		sizeKeyPressed = true;
	}
	else
		sizeKeyPressed = false;
}

static void changeParticleSystem(GLFWwindow *window, ParticleSystemUI &particleSystems) {
	static bool particleSystemKeyPressed = false;

	vector<string> particleSystemsNames = particleSystems.getParticleSystemsNames();
	if (particleSystemsNames.empty())
		return;

	auto currentSystem = find(
		particleSystemsNames.begin(),
		particleSystemsNames.end(),
		particleSystems.getActiveParticleSystemsNames().back()
	);

	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
		if (particleSystemKeyPressed)
			return;

		if (currentSystem == particleSystemsNames.end())
			particleSystems.activate(particleSystemsNames.front());
		else {
			auto nextSystem = currentSystem + 1;
			if (nextSystem == particleSystemsNames.end())
				particleSystems.activate(particleSystemsNames.front());
			else
				particleSystems.activate(*nextSystem);
		}

		particleSystems.deactivate(*currentSystem);
		particleSystemKeyPressed = true;
	}
	else if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
		if (particleSystemKeyPressed)
			return;

		if (currentSystem == particleSystemsNames.begin())
			particleSystems.activate(particleSystemsNames.back());
		else {
			auto previousSystem = currentSystem - 1;
			if (previousSystem == particleSystemsNames.begin())
				particleSystems.activate(particleSystemsNames.back());
			else
				particleSystems.activate(*previousSystem);
		}

		particleSystems.deactivate(*currentSystem);
		particleSystemKeyPressed = true;
	}
	else
		particleSystemKeyPressed = false;
}

// Handle all keyboard & other events
void	handleEvents(GLFWwindow *window, ParticleSystemUI &particleSystems) {
	glfwPollEvents();

	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (RESIZABLE)
		glfwSetFramebufferSizeCallback(window, resize_viewport);

	setFullscreen(window);
	updateFPS(window);
	getMousePos(window);
	changeParticlesSize(window);
	changeParticleSystem(window, particleSystems);

	(void)particleSystems; // To remove
}