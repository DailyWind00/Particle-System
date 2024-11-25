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
	cl::Buffer particles(context, CL_MEM_READ_WRITE, bufferSize);
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