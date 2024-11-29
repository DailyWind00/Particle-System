#version 450 core

layout (location=0) in vec3 fparticlePos;
layout (location=1) in vec3 fparticleVel;
layout (location=2) in float fparticleLife;

out vec4 screenColor;

uniform float time;

void main() {
	vec3 pulse = vec3(sin(abs(time)), cos(abs(time)), 1.0);
	screenColor = vec4(pulse, 1.0);	
}