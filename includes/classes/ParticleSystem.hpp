#pragma once

# include "config.hpp"
# include "Shader.hpp"
# include <vector>
# include <array>

using namespace std;

// Data structure for a particle
// Stored in 7 floats
typedef struct Particle {
	cl_float	position[3];
	cl_float	velocity[3];
	cl_float	life;
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
		
		void	draw();
};

# define NO_LIMIT (size_t)-1

// Example of JSON configuration file:
// particleSystem: [{
//     "name": "string",
//     "particleCount": uint,
//     "shader": ["vertexPath", "fragmentPath"],
//     "kernel": ["kernelPath", ...]
// }, ...]
typedef struct JSONParticleSystemConfig {
	string				name;
	size_t				particleCount;
	array<string, 2>	shaderPaths;
	vector<string>		kernelPaths;

	bool				active;
	ParticleSystem	   *particleSystem = nullptr;
	GLuint				shaderID = 0;
} JSONParticleSystemConfig;
typedef vector<JSONParticleSystemConfig> VJSONParticleSystemConfigs;

// Particle system user interface
// Optional class for a easier control of multiple particle systems
// This class accept JSON configuration files:
class ParticleSystemUI {
	private:
		VJSONParticleSystemConfigs	particleSystems;
		Shader						shaders;
		size_t						globalParticleCount;

	public:
		ParticleSystemUI(const string &JSONConfigPath, size_t globalParticleCount = NO_LIMIT);
		~ParticleSystemUI();

		/// Public functions

		void	activate(const string &systemName);
		void	deactivate(const string &systemName);
		void	drawActivesParticleSystems();

		// Set the uniform to the particle system shader
		template <typename argument>
		void setShaderUniform(const string &systemName, const string &uniformName, const argument &args) {
			auto particleSystem = operator[](systemName);

			if (particleSystem == particleSystems.end())
				throw runtime_error("Particle System \"" + systemName + "\" not found");

			if (!particleSystem->active)
				throw runtime_error("Particle System \"" + systemName + "\" is inactive");

			shaders.setUniform(particleSystem->shaderID, uniformName, args);
		};

		/// Getters

		VJSONParticleSystemConfigs::const_iterator  operator[](const string &systemName) const;
		VJSONParticleSystemConfigs::const_iterator  operator[](const uint &index) const;
		VJSONParticleSystemConfigs::const_iterator  begin() const;
		VJSONParticleSystemConfigs::const_iterator  front() const;
		VJSONParticleSystemConfigs::const_iterator  back() const;
		VJSONParticleSystemConfigs::const_iterator  end() const;
		const size_t				 			   &getGlobalParticleCount() const;
};