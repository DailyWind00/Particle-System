#include "config.hpp"
#include "ParticleSystem.hpp"

// Keep the window alive, exiting this function mean the process is over
static void program_loop(GLFWwindow *window, ParticleSystemUI &particleSystems) {
	float time = 0.0;

	while (!glfwWindowShouldClose(window)) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		getFrametime();
		
		handleEvents(window, particleSystems);

		// Set the uniform for the active particle system
		for (auto particleSystem = particleSystems.begin(); particleSystem != particleSystems.end(); particleSystem++) {
			if (particleSystem->active) {

				particleSystems.setShaderUniform(
					particleSystem->name,
					"mouse",
					(vec2){MOUSE_X, MOUSE_Y}
				);

				cl_float2 mouse;
				mouse.s[0] = MOUSE_X;
				mouse.s[1] = MOUSE_Y;
				particleSystems.setKernelArgs(
					particleSystem->name,
					time,
					mouse
				);
				break;
			}
		}

		particleSystems.drawActivesParticleSystems();

		glfwSwapBuffers(window);

		time += 0.001;
	}
}

// Will call the program loop
void	Rendering(GLFWwindow *window, const string &jsonConfigPath) {
	glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_PROGRAM_POINT_SIZE);
	glPointSize(PARTICLE_SIZE);

	ParticleSystemUI particles(jsonConfigPath);
	particles.activate(particles.front()->name);

	displayCommands();

	printVerbose("Entering program's loop");
	program_loop(window, particles);
	printVerbose("Exiting program's loop");
}