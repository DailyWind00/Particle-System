#include "config.hpp"

int main(int argc, char **argv) {
	if (argc < 2) {
		cout << "> Run the program with the -h flag to display the help message\n";
		exit(EXIT_FAILURE);
	}

	try {
		if (checkFlags(argc, argv) == argc - 1) {
			cerr << BRed << "No json config file specified\n" << ResetColor;
			cout << "> Run the program with the -h flag to display the help message\n";
			exit(EXIT_FAILURE);
		}
	} catch(const exception& e) {
		cerr << BRed << "Flag error : " << e.what() << ResetColor << endl;
		cout << "> Run the program with the -h flag to display the help message\n";
		exit(EXIT_FAILURE);
	}

	try {
		GLFWwindow *window = CreateWindow();
		Rendering(window, argv[argc - 1]);
		DestroyWindow(window);
	}
	catch(const exception& e) {
		cerr << BRed <<  "Critical Error : " << e.what() << ResetColor <<'\n';
		if (string(e.what()).find("CL") != string::npos)
			cerr << BCyan << "You got a OpenCL error, " << CL_ERROR_MSG << " if you want the documentation" << ResetColor << endl;
		exit(EXIT_FAILURE);
	}
}
