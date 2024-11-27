#include "ParticleSystem.hpp"

/// Constructors & Destructors
ParticleSystem::ParticleSystem(size_t ParticleCount) {
	printVerbose("Creating Particle System");

	size_t bufferSize = ParticleCount * sizeof(Particle);
	this->particleCount = ParticleCount;

	createOpenGLBuffers(bufferSize);
	createOpenCLContext();

	printVerbose("Particle System created");
}

ParticleSystem::~ParticleSystem() {
    glDeleteBuffers(1, &VBO);
	glDeleteVertexArrays(1, &VAO);
	printVerbose("Particle System deleted");
}
/// ---


/// Private functions
cl::Device	ParticleSystem::getGPU() const {
	std::vector<cl::Platform> platforms;
	cl::Platform::get(&platforms);
	if (platforms.empty())
		throw std::runtime_error("No OpenCL platforms found");
	cl::Platform platform = platforms[0];

	std::vector<cl::Device> devices;
	platform.getDevices(CL_DEVICE_TYPE_GPU, &devices);
	if (devices.empty())
		throw std::runtime_error("No OpenCL devices found");
	cl::Device device = devices[0];

	return device;
}

// Create OpenCL context with OpenGL interoperability
void	ParticleSystem::createOpenCLContext() {
	printVerbose("> Creating OpenCL context -> ", false);

	cl::Platform platform = cl::Platform::getDefault();
	this->device = getGPU();

	cl_context_properties properties[] = {
		CL_GL_CONTEXT_KHR, (cl_context_properties)glXGetCurrentContext(),
		CL_GLX_DISPLAY_KHR, (cl_context_properties)glXGetCurrentDisplay(),
		CL_CONTEXT_PLATFORM, (cl_context_properties)(platform)(),
		0
	};

	cl_int err;
	this->context = cl::Context(CL_DEVICE_TYPE_GPU, properties, nullptr, nullptr, &err);
	if (err != CL_SUCCESS) {
		printVerbose(BRed + "Error" + ResetColor);
		throw std::runtime_error("Failed to create OpenCL context");
	}

	this->particles = cl::BufferGL(context, CL_MEM_READ_WRITE, VBO); // Interoperability with OpenGL
	
	printVerbose(BGreen + "Context created" + ResetColor);
}

// Create OpenGL buffers for the particles
void	ParticleSystem::createOpenGLBuffers(size_t bufferSize) {
	printVerbose("> Creating OpenGL buffers -> ", false);

    // Vertex array object
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

	// Vertex buffer object
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, bufferSize * sizeof(Particle), nullptr, GL_DYNAMIC_DRAW); // Allocate memory (but don't fill it)

    // Enable vertex attributes and set up their layout
    glEnableVertexAttribArray(0); // Position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Particle), (void*)offsetof(Particle, position));

    glEnableVertexAttribArray(1); // Velocity
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Particle), (void*)offsetof(Particle, velocity));

    glEnableVertexAttribArray(2); // Color
    glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(Particle), (void*)offsetof(Particle, color));

    glEnableVertexAttribArray(3); // Life
    glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, sizeof(Particle), (void*)offsetof(Particle, life));

    glBindVertexArray(0);

	printVerbose(BGreen + "Buffers created" + ResetColor);
}
/// ---



/// Public functions
void	ParticleSystem::update() {
	// TODO
}

void	ParticleSystem::draw() {
	glBindVertexArray(VAO);
	glDrawArrays(GL_POINTS, 0, particleCount * sizeof(Particle));
	glBindVertexArray(0);
}
/// ---