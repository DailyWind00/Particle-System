#version 400 core

layout (location=0) in vec3 particlePos;
layout (location=1) in vec3 particleVel;
layout (location=2) in float particleLife;

out vec4 fragmentColor;

uniform mat4 Transform;
uniform mat4 View;
uniform mat4 Projection;

void main() {
	gl_Position = Projection * View * Transform * vec4(particlePos, 1.0);

	fragmentColor = vec4(1);
}
