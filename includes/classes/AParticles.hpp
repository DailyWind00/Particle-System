#pragma once

#include <array>
#include "config.hpp"

typedef std::array<float, 3> vec3;
typedef std::array<float, 4> vec4;

typedef struct Particle {
	vec3	position;
	vec3	velocity;
	vec4	color;
	float	life;
} Particle;

// This class is an interface to store particles datas.
// The behavior of the particles will be defined in it's children.
// This class set a OpenCL context and a OpenCL queue.
class AParticles {
	private:
		cl::Context context;

		/// Private functions
		cl::Device	getGPU() const;

	protected:
		cl::Buffer particles; // VRAM buffer

	public:
		AParticles(size_t ParticleCount);
		~AParticles();

		/// Public functions
		// virtual void	update() = 0;
		// virtual void	draw()   = 0;
};