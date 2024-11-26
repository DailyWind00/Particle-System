#version 400 core

in vec4 fragmentColor;

out vec4 screenColor;

void main() {
	screenColor = fragmentColor;
}