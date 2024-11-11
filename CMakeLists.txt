cmake_minimum_required(VERSION 3.5.0)
project(Particle-System VERSION 1.0.0)
cmake_policy(SET CMP0072 NEW)

find_package(OpenGL REQUIRED)
find_package(OpenCL REQUIRED)

add_definitions(-DCL_TARGET_OPENCL_VERSION=300) # OpenCL 3.0

add_executable(Particle-System 
	srcs/main.cpp
	srcs/window.cpp
	srcs/routine.cpp
	srcs/events.cpp
	srcs/flags.cpp
	srcs/utils.cpp
	includes/classes/Shader.cpp
	dependencies/stb/stb_config.cpp
	dependencies/glad/glad.c
)
include_directories(${OpenCL_INCLUDE_DIRS})

target_include_directories(Particle-System PRIVATE dependencies)
target_include_directories(Particle-System PRIVATE includes)
target_include_directories(Particle-System PRIVATE includes/classes)

target_compile_options(Particle-System PRIVATE -Wall -Wextra -Werror -O3 -g -fPIE)

target_link_libraries(Particle-System OpenGL::GL glfw)
target_link_libraries(Particle-System ${OpenCL_LIBRARIES})