#version 450 core

layout (location=0) in vec3 vparticlePos;
layout (location=1) in vec3 vparticleVel;
layout (location=2) in float vparticleLife;

layout (location=0) out vec3 fparticlePos;
layout (location=1) out vec3 fparticleVel;
layout (location=2) out float fparticleLife;

void main() {
	gl_Position = vec4(vparticlePos, 1.0);

	fparticlePos = vparticlePos;
	fparticleVel = vparticleVel;
	fparticleLife = vparticleLife;
}
