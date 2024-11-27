#include "ParticleSystem.hpp"

/// Constructors & Destructors
ParticleSystem::ParticleSystem(size_t ParticleCount, const string &kernelProgramPath) {
	printVerbose("Creating Particle System");

	size_t bufferSize = ParticleCount * sizeof(Particle);
	this->particleCount = ParticleCount;

	createOpenGLBuffers(bufferSize);
	createOpenCLContext(kernelProgramPath);

	printVerbose("Particle System created");
}

ParticleSystem::~ParticleSystem() {
    glDeleteBuffers(1, &VBO);
	glDeleteVertexArrays(1, &VAO);
	printVerbose("Particle System deleted");
}
/// ---


/// Private functions

// Create OpenCL context with OpenGL interoperability
void	ParticleSystem::createOpenCLContext(const string &kernelProgramPath) {
	printVerbose("> Creating OpenCL context -> ", false);

	std::vector<cl::Platform> Vplatforms;
	cl::Platform::get(&Vplatforms);
	if (Vplatforms.empty()) {
		printVerbose(BRed + "Error" + ResetColor);
		throw std::runtime_error("No OpenCL platforms found");
	}
	cl::Platform platform = Vplatforms[0];

	std::vector<cl::Device> Vdevices;
	platform.getDevices(CL_DEVICE_TYPE_GPU, &Vdevices);
	if (Vdevices.empty()) {
		printVerbose(BRed + "Error" + ResetColor);
		throw std::runtime_error("No OpenCL devices found");
	}
	this->device = Vdevices[0];

	cl_context_properties properties[] = {
		CL_GL_CONTEXT_KHR, (cl_context_properties)glXGetCurrentContext(),
		CL_GLX_DISPLAY_KHR, (cl_context_properties)glXGetCurrentDisplay(),
		CL_CONTEXT_PLATFORM, (cl_context_properties)(platform)(),
		0
	};

	// Load the kernel program
	ifstream file(kernelProgramPath);
	stringstream kernelSource;
	string line;

	if (!file.is_open()) {
		printVerbose(BRed + "Error" + ResetColor);
		throw runtime_error("Failed to open file " + kernelProgramPath + " : " + (string)strerror(errno));
	}
	while (getline(file, line))
		kernelSource << line << '\n';

	try {
		this->context = cl::Context(CL_DEVICE_TYPE_GPU, properties, nullptr, nullptr);
		this->particles = cl::BufferGL(context, CL_MEM_READ_WRITE, VBO); // Interoperability with OpenGL
		this->queue = cl::CommandQueue(context, device, 0);
		this->program = cl::Program(context, kernelSource.str(), false);
		this->kernel = cl::Kernel(this->program, "updateParticle");
	}
	catch (cl::Error &e) {
		printVerbose(BRed + "Error" + ResetColor);
		throw std::runtime_error("OpenCL error : " + (string)e.what() + " (" + to_string(e.err()) + ")");
	}
	
	printVerbose(BGreen + "Context created" + ResetColor);
	printVerbose("Using device: " + device.getInfo<CL_DEVICE_NAME>());
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

    glEnableVertexAttribArray(2); // Life
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