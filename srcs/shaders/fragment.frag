#version 400 core

in vec4 fragmentColor;

out vec4 screenColor;

uniform float time;

void main() {
	vec3 pulse = vec3(sin(abs(time)), cos(abs(time)), 1.0);
	screenColor = vec4(pulse, 1.0);
}