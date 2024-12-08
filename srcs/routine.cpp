#include "config.hpp"

// Keep the window alive, exiting this function mean the process is over
static void program_loop(GLFWwindow *window, Shader &shaders, ParticleSystem &particles) {
	double time = 0.0;

	while (!glfwWindowShouldClose(window)) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		getFrametime();
		handleEvents(window, shaders);

		particles.update(time);
		particles.draw();

		shaders.setFloat("time", time);

		glfwSwapBuffers(window);

		time += 0.01;
	}
}

// Will call the program loop
void	Rendering(GLFWwindow *window, size_t particleCount) {
	glClearColor(0.02f, 0.02f, 0.175f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	// glEnable(GL_PROGRAM_POINT_SIZE);
	// glPointSize(500.0f);

	vector<string> VkernelProgramPaths = {
		"./srcs/kernels/test.cl"
	};
	ParticleSystem particles(particleCount, VkernelProgramPaths);

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