#pragma once

#include <array>
#include "config.hpp"

typedef array<float, 3> vec3;
typedef array<float, 4> vec4;

// Data structure for a particle
typedef struct Particle {
	vec3	position = {0, 0, 0};
	vec3	velocity = {0, 0, 0};
	vec4	color    = {1, 1, 1, 1};
	float	life     = 0;
} Particle;

// This class is an interface to store particles datas.
// The behavior of the particles will be defined in OpenCL kernel functions.
// This class set a OpenCL context and a OpenCL queue.
class ParticleSystem {
	private:
		// OpenGL variables
		GLuint				vbo;
		GLuint				vao;

		// OpenCL variables
		cl::Device			device;
		cl::Context			context;
		cl::CommandQueue	queue;
		cl::BufferGL		particles; // VRAM buffer

		/// Private functions
		cl::Device	getGPU() const;
		cl::Context	createOpenCLContext() const;

	public:
		ParticleSystem(size_t ParticleCount);
		~ParticleSystem();

		/// Public functions
		void	update();
		void	draw();
};