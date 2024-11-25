#include "AParticles.hpp"

/// Constructors & Destructors
AParticles::AParticles(size_t ParticleCount) {
	cl::Device device = getGPU();
	cl::Context context(device);

	printVerbose("OpenCL context created");
	printVerbose("Using device : " + device.getInfo<CL_DEVICE_NAME>());
	this->context = context;

	// Allocate memory on the VRAM for the particles
	size_t bufferSize = ParticleCount * sizeof(Particle);
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

	this->particles = cl::Buffer(context, CL_MEM_READ_WRITE, bufferSize);
}

AParticles::~AParticles() {
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
/// ---