#include "ParticleSystem.hpp"

/// Constructors & Destructors
ParticleSystem::ParticleSystem(size_t ParticleCount) {
	printVerbose("Creating Particle System");

	size_t bufferSize = ParticleCount * sizeof(Particle);
	this->particleCount = ParticleCount;

	createOpenGLBuffers(bufferSize);

	// Allocate memory on the VRAM for the particles
	this->device = getGPU();
	this->context = createOpenCLContext();

	cl_ulong globalMemSize = device.getInfo<CL_DEVICE_GLOBAL_MEM_SIZE>();
	cl_ulong maxAllocSize = device.getInfo<CL_DEVICE_MAX_MEM_ALLOC_SIZE>();

	printVerbose("Using device : " + device.getInfo<CL_DEVICE_NAME>());
	printVerbose("| Global memory size : " + to_string(globalMemSize / (1024 * 1024)) + " MB");
	printVerbose("| Max allocation size : " + to_string(maxAllocSize / (1024 * 1024)) + " MB");
	printVerbose("> Attempting Allocation of " + to_string(bufferSize / (1024 * 1024)) + " MB on the VRAM -> ", false);

	if (bufferSize > maxAllocSize) {
		printVerbose(BRed + "Error" + ResetColor);
		printVerbose(BCyan + "Tips : Try to decrease the number of particles" + ResetColor);
		throw runtime_error("Failed to allocate memory on the VRAM : Buffer size is too big");
	}
	printVerbose(BGreen + "Memory allocated" + ResetColor);

	this->particles = cl::BufferGL(context, CL_MEM_READ_WRITE, VBO);

	printVerbose("Particle System created");
}

ParticleSystem::~ParticleSystem() {
    glDeleteBuffers(1, &VBO);
	glDeleteVertexArrays(1, &VAO);
	printVerbose("OpenGL buffers deleted");
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
cl::Context	ParticleSystem::createOpenCLContext() const {
	cl::Platform platform = cl::Platform::getDefault();

	cl_context_properties properties[] = {
		CL_GL_CONTEXT_KHR, (cl_context_properties)glXGetCurrentContext(),
		CL_GLX_DISPLAY_KHR, (cl_context_properties)glXGetCurrentDisplay(),
		CL_CONTEXT_PLATFORM, (cl_context_properties)(platform)(),
		0
	};

	cl_int err;
	cl::Context context(CL_DEVICE_TYPE_GPU, properties, nullptr, nullptr, &err);
	if (err != CL_SUCCESS)
		throw std::runtime_error("Failed to create OpenCL context");
	printVerbose("OpenCL context created");

	return context;
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
	glBufferData(GL_ARRAY_BUFFER, bufferSize, nullptr, GL_DYNAMIC_DRAW);

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
	glDrawArrays(GL_POINTS, 0, particleCount);
	glBindVertexArray(0);
}
/// ---