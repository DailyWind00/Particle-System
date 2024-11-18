#include "config.hpp"

double	FRAMETIME = 0;
size_t	FPS = 0;

// Display the help message
void	displayHelp(char *executable_name) {
	cout << BGreen <<"=== 42 Particle-System by DailyWind ===\n" << ResetColor;
	cout << "Usage: " << executable_name << " [options] <.obj file>\n";
	cout << "Options:\n";
	cout << "\t-v, --verbose\t\t\tVerbose mode\n";
	cout << "\t-s, --speed [value]\t\tSet the camera speed (default 1)\n";
	cout << "\t-r, --resizable\t\t\tResizable window\n";
	cout << "\t-k, --keyboard [option]\t\tChange the keyboard language\n";
	cout << LightGray << "\t\t│ > Options availables :                     │\n" << ResetColor;
	cout << LightGray << "\t\t│ azerty : set the keyboard to azerty        │\n" << ResetColor;
	cout << LightGray << "\t\t│ qwerty : set the keyboard to qwerty        │\n" << ResetColor;
	cout << LightGray << "\t\t╰────────────────────────────────────────────╯\n" << ResetColor;
	cout << "\t    --no-tooltip\t\tDisable the commands tooltip in the standard output\n";
	cout << "\t-h, --help\t\t\tDisplay this information\n";
}

// Display the commands available in the program
void	displayCommands() {
	// TODO
}

// Open the file in read mode and return the ifstream object, throw an error if the file can't be opened
ifstream	openReadFile(const string &filename) {
	ifstream file(filename);
	if (!file.is_open())
		throw runtime_error("Failed to open file : " + (string)strerror(errno));
	return file;
}

// Load the texture using stb_image and return the data, throw an error if the texture can't be loaded
unsigned char *stbi_loader(const string &filename, int &width, int &height, int &nrChannels) {
	printVerbose("> Loading texture " + filename + " -> ", false);
	stbi_set_flip_vertically_on_load(true); // Using OpenGL coordinate system

	unsigned char *data = stbi_load(filename.c_str(), &width, &height, &nrChannels, STBI_default);
	if (!data) {
		printVerbose(BRed + "Error" + ResetColor);
		return nullptr;
	}

	printVerbose(BGreen + "Texture loaded" + ResetColor);
	return data;
}

// Print the message on the standard output if VERBOSE is set to true
void	printVerbose(const string &message, bool newline) {
	if (VERBOSE) {
		cout << message;
		if (newline)
			cout << endl;
	}
}

// Calculate the frametime of the program
void getFrametime() {
	static double last_time = glfwGetTime();
	static int frame_count = 0;

	double current_time = glfwGetTime();
	frame_count++;
	if (current_time - last_time >= 1.0) {
		FRAMETIME = 1000.0/double(frame_count);
		FPS = frame_count;
		frame_count = 0;
		last_time += 1.0;
	}
}