// plasma.cl
typedef struct {
    struct {
        float x;
        float y;
        float z;
    } position;

    struct {
        float x;
        float y;
        float z;
    } velocity;

    float life;
} Particle;

float  randRange(float seed, float min, float max);

float	abs(float x) {
	return x < 0.0f ? -x : x;
}

__kernel void update(__global Particle* particles, int particleCount, float time, float2 center) {
	uint id = get_global_id(0); // Get the unique thread ID
	Particle p = particles[id];
	uint seed = randRange(id, 0, particleCount) + (uint)(time * center.x * center.y);

	// Circle pattern
	float angle = randRange(seed * 3, 0.0f, 2.0f * M_PI);
	float radius = randRange(seed * 4, 0.0f, 1.2f);

	center.x += 0.025f * cos(time * 800);
	center.y += 0.025f * sin(time * 800);

	if (p.life <= 0.0f) { // Respawn the particle
		p.position.x = center.x + radius * cos(angle) * 0.2f;
		p.position.y = center.y + radius * sin(angle) * 0.2f;
		p.position.z = 0.0f;

		p.velocity.x = radius * cos(angle) * 0.005f;
		p.velocity.y = radius * sin(angle) * 0.005f;
		p.velocity.z = radius * cos(angle) * sin(angle) * 0.005f;
		
		p.life = 0.75f;
	}

	// Plasma physics
	float2 dir = (float2)(center.x - p.position.x, center.y - p.position.y);
	float dist = length(dir);

	dir.x += dir.x * tan(p.life) * cos(p.life);
	dir.y += dir.y * (1 / tan(p.life)) * sin(p.life);

	p.velocity.x += 0.025f * dir.x * sin(p.life);
	p.velocity.y += 0.025f * dir.y * sin(p.life);

	// Particle physics
	p.position.x += p.velocity.x;
	p.position.y += p.velocity.y;
	p.position.z += p.velocity.z;

	// Fade out the particle
	p.life -= randRange(seed * 5, 0.005f, 0.02);
	if (dist > 0.25f)
		p.life = 0.0f;

	// Update the particle back to the global memory
	particles[id] = p;
}