#pragma once

/// Defines
# define CL_HPP_TARGET_OPENCL_VERSION 200 // OpenCL 2.0
# define CL_HPP_ENABLE_EXCEPTIONS
# define COLOR_HEADER_CXX
# define CL_ERROR_MSG "\033]8;;https://registry.khronos.org/OpenCL/specs/opencl-cplusplus-1.2.pdf\033\\[Click Here]\033]8;;\033\\"

/// System includes
# include <iostream>
# include <glad/glad.h>
# include <GLFW/glfw3.h>
# include <OpenCL/opencl.hpp>
# include <OpenCL/cl_gl.h>
# include <fstream>
# include <string.h>
# include <GL/glx.h>
# include <JSON/json_config.hpp>

/// Custom includes
# include "color.h"
class Shader;
class ParticleSystem;
class ParticleSystemUI;

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
extern float	MOUSE_X, MOUSE_Y;

// Flags (default values are set in flags.cpp)
extern bool					RESIZABLE;
extern bool					VERBOSE;
extern bool					SHOW_TOOLTIP;
extern int					PARTICLE_SIZE;
extern KEYBOARD_LANGUAGE	KEYBOARD;

/// Functions
// window.cpp
GLFWwindow		*CreateWindow();
void			DestroyWindow(GLFWwindow *window);

// routine.cpp
void			Rendering(GLFWwindow *window, const string &jsonConfigPath);

// events.cpp
void			handleEvents(GLFWwindow *window, ParticleSystemUI &particleSystems);

// flags.cpp
int				checkFlags(int argc, char **argv);

// utils.cpp
void			displayHelp(char *executable_name);
void			displayCommands();
void			printVerbose(const string &message, bool newline = true);
void			getFrametime();