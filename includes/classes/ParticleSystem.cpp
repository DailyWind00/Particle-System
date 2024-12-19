#include "ParticleSystem.hpp"

/// Constructors & Destructors

// Create a particle system with a given name, a number of particles and a list of OpenCL kernel programs
// The kernel programs are loaded from the files in VkernelProgramPaths
// The kernel program will begin from the "update" function
ParticleSystem::ParticleSystem(size_t ParticleCount, const vector<string> &VkernelProgramPaths) {
	printVerbose("Creating Particle System");

	size_t bufferSize = ParticleCount * sizeof(Particle);
	this->particleCount = ParticleCount;

	createOpenGLBuffers(bufferSize);
	createOpenCLContext(VkernelProgramPaths);

	printVerbose("Particle System created");
}

ParticleSystem::~ParticleSystem() {
    glDeleteBuffers(1, &VBO);
	glDeleteVertexArrays(1, &VAO);
	printVerbose("Particle System deleted");
}
/// ---



/// Private functions

// Get the string representation of an OpenCL error
const string	ParticleSystem::CLstrerrno(cl_int error) {
	switch(error) {
		// run-time and JIT compiler errors
		case 0: return "CL_SUCCESS";
		case -1: return "CL_DEVICE_NOT_FOUND";
		case -2: return "CL_DEVICE_NOT_AVAILABLE";
		case -3: return "CL_COMPILER_NOT_AVAILABLE";
		case -4: return "CL_MEM_OBJECT_ALLOCATION_FAILURE";
		case -5: return "CL_OUT_OF_RESOURCES";
		case -6: return "CL_OUT_OF_HOST_MEMORY";
		case -7: return "CL_PROFILING_INFO_NOT_AVAILABLE";
		case -8: return "CL_MEM_COPY_OVERLAP";
		case -9: return "CL_IMAGE_FORMAT_MISMATCH";
		case -10: return "CL_IMAGE_FORMAT_NOT_SUPPORTED";
		case -11: return "CL_BUILD_PROGRAM_FAILURE";
		case -12: return "CL_MAP_FAILURE";
		case -13: return "CL_MISALIGNED_SUB_BUFFER_OFFSET";
		case -14: return "CL_EXEC_STATUS_ERROR_FOR_EVENTS_IN_WAIT_LIST";
		case -15: return "CL_COMPILE_PROGRAM_FAILURE";
		case -16: return "CL_LINKER_NOT_AVAILABLE";
		case -17: return "CL_LINK_PROGRAM_FAILURE";
		case -18: return "CL_DEVICE_PARTITION_FAILED";
		case -19: return "CL_KERNEL_ARG_INFO_NOT_AVAILABLE";

		// compile-time errors
		case -30: return "CL_INVALID_VALUE";
		case -31: return "CL_INVALID_DEVICE_TYPE";
		case -32: return "CL_INVALID_PLATFORM";
		case -33: return "CL_INVALID_DEVICE";
		case -34: return "CL_INVALID_CONTEXT";
		case -35: return "CL_INVALID_QUEUE_PROPERTIES";
		case -36: return "CL_INVALID_COMMAND_QUEUE";
		case -37: return "CL_INVALID_HOST_PTR";
		case -38: return "CL_INVALID_MEM_OBJECT";
		case -39: return "CL_INVALID_IMAGE_FORMAT_DESCRIPTOR";
		case -40: return "CL_INVALID_IMAGE_SIZE";
		case -41: return "CL_INVALID_SAMPLER";
		case -42: return "CL_INVALID_BINARY";
		case -43: return "CL_INVALID_BUILD_OPTIONS";
		case -44: return "CL_INVALID_PROGRAM";
		case -45: return "CL_INVALID_PROGRAM_EXECUTABLE";
		case -46: return "CL_INVALID_KERNEL_NAME";
		case -47: return "CL_INVALID_KERNEL_DEFINITION";
		case -48: return "CL_INVALID_KERNEL";
		case -49: return "CL_INVALID_ARG_INDEX";
		case -50: return "CL_INVALID_ARG_VALUE";
		case -51: return "CL_INVALID_ARG_SIZE";
		case -52: return "CL_INVALID_KERNEL_ARGS";
		case -53: return "CL_INVALID_WORK_DIMENSION";
		case -54: return "CL_INVALID_WORK_GROUP_SIZE";
		case -55: return "CL_INVALID_WORK_ITEM_SIZE";
		case -56: return "CL_INVALID_GLOBAL_OFFSET";
		case -57: return "CL_INVALID_EVENT_WAIT_LIST";
		case -58: return "CL_INVALID_EVENT";
		case -59: return "CL_INVALID_OPERATION";
		case -60: return "CL_INVALID_GL_OBJECT";
		case -61: return "CL_INVALID_BUFFER_SIZE";
		case -62: return "CL_INVALID_MIP_LEVEL";
		case -63: return "CL_INVALID_GLOBAL_WORK_SIZE";
		case -64: return "CL_INVALID_PROPERTY";
		case -65: return "CL_INVALID_IMAGE_DESCRIPTOR";
		case -66: return "CL_INVALID_COMPILER_OPTIONS";
		case -67: return "CL_INVALID_LINKER_OPTIONS";
		case -68: return "CL_INVALID_DEVICE_PARTITION_COUNT";

		// extension errors
		case -1000: return "CL_INVALID_GL_SHAREGROUP_REFERENCE_KHR";
		case -1001: return "CL_PLATFORM_NOT_FOUND_KHR";
		case -1002: return "CL_INVALID_D3D10_DEVICE_KHR";
		case -1003: return "CL_INVALID_D3D10_RESOURCE_KHR";
		case -1004: return "CL_D3D10_RESOURCE_ALREADY_ACQUIRED_KHR";
		case -1005: return "CL_D3D10_RESOURCE_NOT_ACQUIRED_KHR";
		default: return "Unknown OpenCL error";
	}
}

// Get the first OpenCL platform
cl::Platform	ParticleSystem::getPlatform() {
	vector<cl::Platform> platforms;
	cl::Platform::get(&platforms);
	if (platforms.empty())
		throw runtime_error("No OpenCL platforms found");

	return platforms.front();
}

// Get the first GPU device from the platform
cl::Device	ParticleSystem::getDevice(const cl::Platform &platform) {
	vector<cl::Device> devices;
	platform.getDevices(CL_DEVICE_TYPE_GPU, &devices);
	if (devices.empty())
		throw runtime_error("No OpenCL devices found");

	return devices.front();
}

// Create an OpenCL context with OpenGL interoperability based on the operating system
cl::Context	ParticleSystem::createContext(const cl::Device &device, const cl::Platform &platform) {
	#if defined(__linux__) || defined(__unix__)
		cl_context_properties properties[] = { // Interoperability with OpenGL (Linux)
			CL_GL_CONTEXT_KHR, (cl_context_properties)glXGetCurrentContext(),
			CL_GLX_DISPLAY_KHR, (cl_context_properties)glXGetCurrentDisplay(),
			CL_CONTEXT_PLATFORM, (cl_context_properties)(platform)(),
			0
		};
	#elif __APPLE__
		cl_context_properties properties[] = { // Interoperability with OpenGL (MacOS)
			CL_CONTEXT_PROPERTY_USE_CGL_SHAREGROUP_APPLE, (cl_context_properties)CGLGetShareGroup(CGLGetCurrentContext()),
			0
		};
	#elif _WIN32
		cl_context_properties properties[] = { // Interoperability with OpenGL (Windows)
			CL_GL_CONTEXT_KHR, (cl_context_properties)wglGetCurrentContext(),
			CL_WGL_HDC_KHR, (cl_context_properties)wglGetCurrentDC(),
			CL_CONTEXT_PLATFORM, (cl_context_properties)(platform)(),
			0
		};
	#endif

	cl::Context context(device, properties);
	return context;
}

// Build a OpenCL program from files in VkernelProgramPaths
cl::Program	ParticleSystem::buildProgram(const vector<string> &VkernelProgramPaths) {
	cl::Program::Sources sources;

	// Load the kernel program from the files
	for (const string &kernelProgramPath : VkernelProgramPaths) {
		ifstream file(kernelProgramPath);
		stringstream kernelSource;
		string line;

		if (!file.is_open()) {
			printVerbose(BRed + "Error" + ResetColor);
			throw runtime_error("Failed to open file " + kernelProgramPath + " : " + (string)strerror(errno));
		}

		kernelSource << file.rdbuf();
		sources.push_back(kernelSource.str());
		file.close();
	}

    cl::Program program(context, sources);
	try {
		program.build({device});
	}
	catch (const cl::Error &e) {
		if (e.err() == CL_BUILD_PROGRAM_FAILURE) {
			string log = program.getBuildInfo<CL_PROGRAM_BUILD_LOG>(device);	
			throw runtime_error("clBuildProgram (CL_BUILD_PROGRAM_FAILURE) :\n" + log);
		}
		else
			throw e;
	}

	return program;
}

// Create OpenCL context with OpenGL interoperability
void	ParticleSystem::createOpenCLContext(const vector<string> &VkernelProgramPaths) {
	printVerbose("> Creating OpenCL context -> ", false);

	try {
		this->platform = getPlatform();
		this->device = getDevice(platform);
		this->context = createContext(device, platform);
		this->program = buildProgram(VkernelProgramPaths);
		this->kernel = cl::Kernel(program, "update");
		this->particles = cl::BufferGL(context, CL_MEM_READ_WRITE, VBO); // Interoperability with OpenGL
		this->queue = cl::CommandQueue(context, device, CL_QUEUE_PROFILING_ENABLE); // Remove profiling when project is finished
		this->memObjects.push_back(particles);
	}
	catch (const cl::Error &e) {
		printVerbose(BRed + "Error" + ResetColor);
		throw runtime_error("OpenCL error : " + (string)e.what() + " (" + CLstrerrno(e.err()) + ")");
	}
	catch (const runtime_error &e) {
		printVerbose(BRed + "Error" + ResetColor);
		throw runtime_error("OpenCL error : " + (string)e.what());
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
    glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, sizeof(Particle), (void*)offsetof(Particle, life));

	glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

	printVerbose(BGreen + "Buffers created" + ResetColor);
}
/// ---



/// Public functions
void	ParticleSystem::printParticlePositions(const std::string& label) { // to remove
	if (particleCount > 10)
		return;
    cout << label << endl;
    // Map the OpenGL buffer to access the particle data
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    Particle* particleData = (Particle*)glMapBuffer(GL_ARRAY_BUFFER, GL_READ_ONLY);
    if (particleData) {
        for (size_t i = 0; i < particleCount; ++i) {
			std::cout << "Particle " << i << ": [" 
					  << particleData[i].position.x << ",\t" 
					  << particleData[i].position.y << ",\t" 
					  << particleData[i].position.z << ",\t"
					  << particleData[i].velocity.x << ",\t" 
					  << particleData[i].velocity.y << ",\t" 
					  << particleData[i].velocity.z << ",\t"
					  << particleData[i].life << "]" << endl;
					  
        }
        glUnmapBuffer(GL_ARRAY_BUFFER);
    }
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void	ParticleSystem::draw() {
	static cl_float	time = 0;

	try {
		printParticlePositions("Before update");

		// Set the kernel arguments
		cl_float2 mouse;
		mouse.s[0] = WINDOW_HEIGHT;
		mouse.s[1] = WINDOW_WIDTH;

		kernel.setArg(0, particles);
		kernel.setArg(1, (cl_int)particleCount);
		kernel.setArg(2, time);
		kernel.setArg(3, mouse);

		// Execute the kernel
		queue.enqueueAcquireGLObjects(&memObjects);
		queue.enqueueNDRangeKernel(kernel, cl::NullRange, cl::NDRange(particleCount), cl::NullRange);
		queue.enqueueReleaseGLObjects(&memObjects);
		queue.finish();

		printParticlePositions("After update");

		glBindVertexArray(VAO);
		glDrawArrays(GL_POINTS, 0, particleCount);
		glBindVertexArray(0);

		time += 0.1f;
	}
	catch (const cl::Error &e) {
		throw runtime_error("OpenCL error : " + (string)e.what() + " (" + CLstrerrno(e.err()) + ")");
	}
}
/// ---