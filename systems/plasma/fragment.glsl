#version 450 core

layout (location=0) in vec3 fparticlePos;
layout (location=1) in vec3 fparticleVel;
layout (location=2) in float fparticleLife;

out vec4 screenColor;

uniform vec2	mouse;

// Generate a random float based on a seed
float randomFloat(vec2 seed) {
    return fract(sin(dot(seed, vec2(12.9898, 78.233))) * 43758.5453);
}

// Generate a random float between min and max
float randRange(vec2 seed, float min, float max) {
    return min + randomFloat(seed) * (max - min);
}

void main() {
	vec2 seed = vec2(fparticlePos.x * 1000.0f, fparticlePos.y * 1000.0f);
	float dist = length(vec2(mouse.x - fparticlePos.x, mouse.y - fparticlePos.y));
	float alpha = smoothstep(1.0f, 0.0f, dist);
	float speed = length(fparticleVel) * 50;

	vec4 purple = vec4(0.5f, 0.0f, 1.0f, alpha);
	vec4 pink = vec4(1.0f, 0.0f, 0.5f, alpha);
	vec4 white = vec4(1.0f, 1.0f, 1.0f, alpha);
	vec4 gold = vec4(1.0f, 0.84f, 0.10f, alpha);
	vec4 blood = vec4(0.5f, 0.0f, 0.0f, alpha);

	vec4 warped = mix(mix(purple, white, fparticleLife), mix(purple, pink, fparticleLife), speed);

	vec4 final;
	if (randRange(seed, 0.0f, 1.0f) < 0.5f)
		final = mix(warped, gold, dist * 2.5f);
	else
		final = mix(warped, blood, dist * 2.5f);

	screenColor = final;
}