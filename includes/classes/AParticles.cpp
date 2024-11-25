#include "AParticles.hpp"

/// Constructors & Destructors
AParticles::AParticles(size_t ParticleCount) {
	size_t bufferSize = ParticleCount * sizeof(Particle);
	cl::Device device = getGPU();
	cl::Context context = createOpenCLContext();

	printVerbose("Using device : " + device.getInfo<CL_DEVICE_NAME>());

	// Vertex buffer object
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, bufferSize, nullptr, GL_DYNAMIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// Allocate memory on the VRAM for the particles
	cl_ulong globalMemSize = device.getInfo<CL_DEVICE_GLOBAL_MEM_SIZE>();
	cl_ulong maxAllocSize = device.getInfo<CL_DEVICE_MAX_MEM_ALLOC_SIZE>();

	printVerbose("| Global memory size : " + to_string(globalMemSize / (1024 * 1024)) + " MB");
	printVerbose("| Max allocation size : " + to_string(maxAllocSize / (1024 * 1024)) + " MB");
	printVerbose("> Attempting Allocation of " + to_string(bufferSize / (1024 * 1024)) + " MB on the VRAM -> ", false);

	if (bufferSize > maxAllocSize) {
		printVerbose(BRed + "Error" + ResetColor);
		printVerbose(BCyan + "Tips : Try to decrease the number of particles" + ResetColor);
		throw runtime_error("Failed to allocate memory on the VRAM : Buffer size is too big");
	}
	printVerbose(BGreen + "Memory allocated" + ResetColor);

	this->particles = cl::BufferGL(context, CL_MEM_READ_WRITE, vbo);
}

AParticles::~AParticles() {
    glDeleteBuffers(1, &vbo);
}
/// ---


/// Private functions
cl::Device	AParticles::getGPU() const {
	std::vector<cl::Platform> platforms;
	cl::Platform::get(&platforms);
	cl::Platform platform = platforms[0];

	std::vector<cl::Device> devices;
	platform.getDevices(CL_DEVICE_TYPE_GPU, &devices);
	cl::Device device = devices[0];

	return device;
}

// Create OpenCL context with OpenGL interoperability
cl::Context	AParticles::createOpenCLContext() const {
	cl_int err;
	cl::Platform platform = cl::Platform::getDefault();

	cl_context_properties properties[] = {
		CL_GL_CONTEXT_KHR, (cl_context_properties)glXGetCurrentContext(),
		CL_GLX_DISPLAY_KHR, (cl_context_properties)glXGetCurrentDisplay(),
		CL_CONTEXT_PLATFORM, (cl_context_properties)(platform)(),
		0
	};

	cl::Context context(CL_DEVICE_TYPE_GPU, properties, nullptr, nullptr, &err);
	if (err != CL_SUCCESS)
		throw std::runtime_error("Failed to create OpenCL context");
	printVerbose("OpenCL context created");

	return context;
}
/// ---