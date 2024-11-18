#pragma once

/// System includes
# include <iostream>
# include <glad/glad.h>
# include <GLFW/glfw3.h>
# include <stb/stb_image.h>
# include <glm/glm.hpp>
# include <CL/cl.h>
# include <fstream>
# include <string.h>

/// Custom includes
# define COLOR_HEADER_CXX
# include "color.h"
# include "Shader.hpp"
class Shader;

/// Defines

/// Global variables
using namespace std;
enum class ROTATION;

enum class KEYBOARD_LANGUAGE {
	AZERTY,
	QWERTY
};

extern int		WINDOW_WIDTH;
extern int		WINDOW_HEIGHT;
extern double	FRAMETIME;
extern size_t	FPS;
extern float	FOV;

// Flags (default values are set in flags.cpp)
extern bool					RESIZABLE;
extern bool					VERBOSE;
extern bool					SHOW_TOOLTIP;
extern bool					SPEED;
extern KEYBOARD_LANGUAGE	KEYBOARD;

/// Functions
// window.cpp
GLFWwindow		*CreateWindow();
void			DestroyWindow(GLFWwindow *window);

// routine.cpp

// events.cpp

// flags.cpp
int				checkFlags(int argc, char **argv);

// utils.cpp
void			displayHelp(char *executable_name);
void			displayCommands();
ifstream		openReadFile(const string &filename);
unsigned char	*stbi_loader(const string &filename, int &width, int &height, int &nrChannels);
void			printVerbose(const string &message, bool newline = true);
void			getFrametime();