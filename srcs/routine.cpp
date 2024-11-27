#include "config.hpp"

// Keep the window alive, exiting this function mean the process is over
static void program_loop(GLFWwindow *window, Shader &shaders, ParticleSystem &particles) {
	while (!glfwWindowShouldClose(window)) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		getFrametime();
		handleEvents(window, shaders);

		particles.update();
		particles.draw();

		glfwSwapBuffers(window);
	}
}

// Will call the program loop
void	Rendering(GLFWwindow *window, ParticleSystem &particles) {
	glClearColor(0.02f, 0.02f, 0.175f, 1.0f);
	glEnable(GL_DEPTH_TEST);

	Shader shaders;
	shaders.add_shader(
		"./srcs/shaders/vertex.vert",
		"./srcs/shaders/fragment.frag",
		"particleShader"
	);

	displayCommands();

	printVerbose("Entering program's loop");
	program_loop(window, shaders, particles);
	printVerbose("Exiting program's loop");
}