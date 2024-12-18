#pragma once

# include "config.hpp"
# include <vector>
# include <array>

using namespace std;
typedef array<float, 3> vec3;
typedef array<float, 4> vec4;

// Data structure for a particle
typedef struct Particle {
	vec3	position = {50, 50, 50};
	vec3	velocity = {10, 10, 10};
	float	life     = 10;
} Particle;

// This class is an interface to store particles datas.
// The behavior of the particles will be defined in OpenCL kernel functions.
// This class set a OpenCL context and a OpenCL queue.
class ParticleSystem {
	private:
		// OpenGL variables
		
		GLuint				VBO;
		GLuint				VAO;

		// OpenCL variables (may be in vector for multiple kernels)

		cl::Platform		platform;
		cl::Device			device;
		cl::Context			context;
		cl::Program			program;
		cl::Kernel			kernel;
		cl::BufferGL		particles; // VRAM buffer
		cl::CommandQueue	queue;
		vector<cl::Memory>	memObjects;

		// Other variables

		size_t				particleCount;

		/// Private functions

		const string	CLstrerrno(cl_int error);
		cl::Platform	getPlatform();
		cl::Device		getDevice(const cl::Platform &platform);
		cl::Context		createContext(const cl::Device &device, const cl::Platform &platform);
		cl::Program		buildProgram(const vector<string> &VkernelProgramPaths);
		void			createOpenGLBuffers(size_t bufferSize);
		void			createOpenCLContext(const vector<string> &VkernelProgramPaths);

	public:
		ParticleSystem(size_t ParticleCount, const vector<string> &VkernelProgramPaths);
		~ParticleSystem();

		/// Public functions

		void	update(float time);
		void	draw();
};