#version 450 core

layout (location=0) in vec3 fparticlePos;
layout (location=1) in vec3 fparticleVel;
layout (location=2) in float fparticleLife;

out vec4 screenColor;

uniform float time;

void main() {
	screenColor = vec4(1.0, 1.0, 1.0, 1.0);
}