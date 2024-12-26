#include "config.hpp"
#include "ParticleSystem.hpp"

// Keep the window alive, exiting this function mean the process is over
static void program_loop(GLFWwindow *window, ParticleSystemUI &particleSystems) {
	float time = 0.0;

	while (!glfwWindowShouldClose(window)) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		getFrametime();
		
		handleEvents(window, particleSystems);

		particleSystems.setUniform("blackhole", "mouse", (vec2){MOUSE_X, MOUSE_Y});
		particleSystems.drawActivesParticles();

		glfwSwapBuffers(window);

		time += 0.001 * FRAMETIME;
	}
}

// Will call the program loop
void	Rendering(GLFWwindow *window, size_t particleCount) {
	glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_PROGRAM_POINT_SIZE);
	glPointSize(PARTICLE_SIZE);

	(void)particleCount;
	ParticleSystemUI particles("./config.json");
	particles.activate("blackhole");
	// particles.activate("rain");

	displayCommands();

	printVerbose("Entering program's loop");
	program_loop(window, particles);
	printVerbose("Exiting program's loop");
}