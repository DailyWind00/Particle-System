#pragma once

#include <array>
#include "config.hpp"

using namespace std;
typedef array<float, 3> vec3;
typedef array<float, 4> vec4;

// Data structure for a particle
typedef struct Particle {
	vec3	position = {50, 50, 50};
	vec3	velocity = {0, 0, 0};
	float	life     = 0;
} Particle;

// This class is an interface to store particles datas.
// The behavior of the particles will be defined in OpenCL kernel functions.
// This class set a OpenCL context and a OpenCL queue.
class ParticleSystem {
	private:
		// OpenGL variables
		GLuint				VBO;
		GLuint				VAO;

		// OpenCL variables
		cl::Device			device;
		cl::Context			context;
		cl::CommandQueue	queue;
		cl::Program			program; // May change to vector<cl::Program> if multiple kernels
		cl::Kernel			kernel;
		cl::BufferGL		particles; // VRAM buffer

		// Other variables
		size_t				particleCount;
		string				systemName;

		/// Private functions

		const string	CLstrerrno(cl_int error);
		cl::Program		buildProgram(const vector<string> &VkernelProgramPaths);
		void			createOpenGLBuffers(size_t bufferSize);
		void			createOpenCLContext(const vector<string> &VkernelProgramPaths);

	public:
		ParticleSystem(const string &SystemName, size_t ParticleCount, const vector<string> &VkernelProgramPaths);
		~ParticleSystem();

		/// Public functions

		void	update();
		void	draw();
};