#pragma once

#include <array>
#include "config.hpp"

typedef std::array<float, 3> vec3;
typedef std::array<float, 4> vec4;

// Data structure for a particle
typedef struct Particle {
	vec3	position = {0, 0, 0};
	vec3	velocity = {0, 0, 0};
	vec4	color    = {1, 1, 1, 1};
	float	life     = 0;
} Particle;

// This class is an interface to store particles datas.
// The behavior of the particles will be defined in it's children.
// This class set a OpenCL context and a OpenCL queue.
class AParticles {
	private:
		/// Private functions
		cl::Device	getGPU() const;
		cl::Context	createOpenCLContext() const;

	protected:
		GLuint			vbo;
		cl::BufferGL	particles; // VRAM buffer

	public:
		AParticles(size_t ParticleCount);
		virtual ~AParticles() = 0;

		/// Public functions
		virtual void	update() = 0;
		virtual void	draw()   = 0;
};