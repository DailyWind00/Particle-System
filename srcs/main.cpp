#include "config.hpp"

int main(int argc, char **argv) {
	if (argc < 2) {
		cout << "> Run the program with the -h flag to display the help message\n";
		exit(EXIT_FAILURE);
	}

	try {
		if (checkFlags(argc, argv) == argc - 1) {
			cerr << BRed << "No file specified\n" << ResetColor;
			cout << "> Run the program with the -h flag to display the help message\n";
			exit(EXIT_FAILURE);
		}
	} catch(const std::exception& e) {
		cerr << BRed << "Flag error : " << e.what() << ResetColor << endl;
		cout << "> Run the program with the -h flag to display the help message\n";
		exit(EXIT_FAILURE);
	}

	size_t particleCount = 0;
	stringstream ss(argv[argc - 1]);
	ss >> particleCount;
	if (ss.fail()) {
		cerr << BRed << "Invalid particle count\n" << ResetColor;
		exit(EXIT_FAILURE);
	}

	try {
		GLFWwindow *window = CreateWindow();
		Rendering(window, particleCount);
		DestroyWindow(window);
	}
	catch(const std::exception& e) {
		cerr << BRed <<  "Critical Error : " << e.what() << ResetColor <<'\n';
		exit(EXIT_FAILURE);
	}
}


// // To remove
// #include <vector>
// #include <iostream>
// #include <fstream>
// #include <sstream>

// // Function to load kernel from file
// std::string loadKernelSource(const std::string& filePath) {
//     std::ifstream file(filePath);
//     if (!file.is_open()) {
//         throw std::runtime_error("Failed to open kernel file: " + filePath);
//     }
//     std::ostringstream oss;
//     oss << file.rdbuf();
//     return oss.str();
// }

// int main() {
//     try {
//         // Load kernel source from file
//         std::string kernelSource = loadKernelSource("./srcs/kernels/test.cl");

//         // Initialize OpenCL
//         std::vector<cl::Platform> platforms;
//         cl::Platform::get(&platforms);
//         cl::Platform platform = platforms.front();

//         std::vector<cl::Device> devices;
//         platform.getDevices(CL_DEVICE_TYPE_GPU, &devices);
//         cl::Device device = devices.front();

//         cl::Context context(device);
//         cl::CommandQueue queue(context, device);

//         // Create and build program
//         cl::Program program(context, kernelSource);
//         program.build({device});

//         // Create buffers
//         std::vector<float> a(1024, 1.0f);
//         std::vector<float> b(1024, 2.0f);
//         std::vector<float> c(1024);

//         cl::Buffer bufferA(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, sizeof(float) * a.size(), a.data());
//         cl::Buffer bufferB(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, sizeof(float) * b.size(), b.data());
//         cl::Buffer bufferC(context, CL_MEM_WRITE_ONLY, sizeof(float) * c.size());

//         // Set up kernel
//         cl::Kernel kernel(program, "add");
//         kernel.setArg(0, bufferA);
//         kernel.setArg(1, bufferB);
//         kernel.setArg(2, bufferC);

//         // Execute kernel
//         queue.enqueueNDRangeKernel(kernel, cl::NullRange, cl::NDRange(1024));
//         queue.finish();

//         // Read results
//         queue.enqueueReadBuffer(bufferC, CL_TRUE, 0, sizeof(float) * c.size(), c.data());

//         // Output results
//         std::cout << "Result: " << c[0] << std::endl; // Should print 3.0
//     } catch (const std::exception& e) {
//         std::cerr << "Error: " << e.what() << std::endl;
//     }

//     return 0;
// }
