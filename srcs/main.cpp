#include "config.hpp"

void testOpenCL() {
    cl_uint platformCount;
    cl_platform_id platforms[10];

    // Get the number of platforms
    cl_int err = clGetPlatformIDs(10, platforms, &platformCount);
    if (err != CL_SUCCESS) {
        std::cerr << "Error: Failed to get platform IDs. Error code: " << err << std::endl;
        return;
    }

    std::cout << "Number of OpenCL platforms found: " << platformCount << std::endl;
    for (cl_uint i = 0; i < platformCount; ++i) {
        char platformName[128];
        clGetPlatformInfo(platforms[i], CL_PLATFORM_NAME, 128, platformName, nullptr);
        std::cout << "Platform " << i + 1 << ": " << platformName << std::endl;
    }
}

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

	const string file_name(argv[argc - 1]);

	try {
		GLFWwindow *window = CreateWindow();

		// Tests to removes
		testOpenCL();
		
		while (!glfwWindowShouldClose(window)) {
			glfwSwapBuffers(window);
			glfwPollEvents();
			getFrametime();
			static size_t previousFPS = 0;
			if (FPS != previousFPS) {
				const string title = "42 Particle-System by DailyWind - FPS : " + to_string(FPS);
				glfwSetWindowTitle(window, title.c_str());
				previousFPS = FPS;
			}
			if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
				glfwSetWindowShouldClose(window, true);
		}
		// ---

		// Main loop call

		DestroyWindow(window);
	}
	catch(const std::exception& e) {
		cerr << BRed <<  "Critical Error : " << e.what() << ResetColor <<'\n';
		exit(EXIT_FAILURE);
	}
}