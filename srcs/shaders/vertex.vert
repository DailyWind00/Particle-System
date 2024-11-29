#version 450 core

layout (location=0) in vec3 vparticlePos;
layout (location=1) in vec3 vparticleVel;
layout (location=2) in float vparticleLife;

layout (location=0) out vec3 fparticlePos;
layout (location=1) out vec3 fparticleVel;
layout (location=2) out float fparticleLife;

uniform mat4 Transform;
uniform mat4 View;
uniform mat4 Projection;

void main() {
	gl_Position = Projection * View * Transform * vec4(vparticlePos, 1.0);

	fparticlePos = vparticlePos;
	fparticleVel = vparticleVel;
	fparticleLife = vparticleLife;
}
