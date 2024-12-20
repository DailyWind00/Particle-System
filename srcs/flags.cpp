#include "config.hpp"

bool				RESIZABLE = false;
bool				VERBOSE = false;
bool				SHOW_TOOLTIP = true;
int					PARTICLE_SIZE = 1;
KEYBOARD_LANGUAGE	KEYBOARD = KEYBOARD_LANGUAGE::QWERTY;

static int setflagVerbose(bool value) {
	VERBOSE = value;
	return 1;
}

static int setflagResizable(bool value) {
	RESIZABLE = value;
	return 1;
}

static int setflagSize(int &i, int argc, char **argv) {
	if (i == argc - 1)
		throw runtime_error("No particle size argument");

	stringstream ss(argv[++i]);
	ss >> PARTICLE_SIZE;

	if (!ss)
		throw runtime_error("Invalid particle size argument");
	if (PARTICLE_SIZE <= 0)
		throw runtime_error("Particle size must be greater than 0");
	
	return 2;
}

static int setflagShowTooltip(bool value) {
	SHOW_TOOLTIP = value;
	return 1;
}

static int setflagKeyboardLanguage(string &arg, int &i, int argc, char **argv) {
	if (i == argc - 1)
		throw runtime_error("No keyboard language argument");

	arg = argv[++i];
	if (arg == "azerty")
		KEYBOARD = KEYBOARD_LANGUAGE::AZERTY;
	else if (arg == "qwerty")
		KEYBOARD = KEYBOARD_LANGUAGE::QWERTY;
	else
		throw runtime_error("Invalid keyboard language argument");

	return 2;
}

// return the number of flags
int	checkFlags(int argc, char **argv) {
	int flags = 0;
	int i;

	for (i = 1; i < argc; i++) {
		string arg(argv[i]);
		if (arg[0] != '-' && arg.substr(0, 2) != "--" && i != argc - 1) {
			throw runtime_error("Not a flag \"" + arg + "\"");
		}

		if (arg == "-v" || arg == "--verbose")
			flags += setflagVerbose(true);

		else if (arg == "-r" || arg == "--resizable")
			flags += setflagResizable(true);

		else if (arg == "-s" || arg == "--size")
			flags += setflagSize(i, argc, argv);

		else if (arg == "-k" || arg == "--keyboard")
			flags += setflagKeyboardLanguage(arg, i, argc, argv);

		else if (arg == "--no-tooltip")
			flags += setflagShowTooltip(false);

		else if (arg == "-h" || arg == "--help") {
			displayHelp(argv[0]);
			exit(EXIT_SUCCESS);
		}
		else {
			if (i == argc - 1 && arg[0] != '-') // object file
				return flags;
			throw runtime_error("Unknown flag \"" + arg + "\"");
		}
	}

	return flags;
}