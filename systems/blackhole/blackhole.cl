// blackhole.cl
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

__kernel void update(__global Particle* particles, int particleCount, float time, float2 center) {
	uint id = get_global_id(0); // Get the unique thread ID
	Particle p = particles[id];
	uint seed = randRange(id, 0, particleCount) + (uint)(time * 1000.0f);

	if (p.life <= 0.0f) { // Respawn the particle
		// Generate random positions in a circle shape just outside the window
		float angle = randRange(seed, 0.0f, 2.0f * M_PI);
		float radius = randRange(seed * 2, 0.35f, 1.2f);
		p.position.x = center.x + radius * cos(angle) * 0.5f;
		p.position.y = center.y + radius * sin(angle) * 0.5f;
		p.position.z = 0.0f;

		p.velocity.x = 0.0f;
		p.velocity.y = 0.0f;
		p.velocity.z = 0.0f;
		
		p.life = 1.0f;
	}

	// Black hole physics
	float2 dir = (float2)(center.x - p.position.x, center.y - p.position.y);
	float dist = length(dir);
	p.velocity.x += dir.x / dist * randRange(seed * 5, 0.0005f, 0.00075f);
	p.velocity.y += dir.y / dist * randRange(seed * 5, 0.0005f, 0.00075f);

	// Spin around the center
	float spinSpeed = 0.01f;
	float2 perpendicular = (float2)(-dir.y, dir.x);
	p.velocity.x += perpendicular.x * spinSpeed * 0.01f;
	p.velocity.y += perpendicular.y * spinSpeed * 0.01f;

	// Particle physics
	p.position.x += p.velocity.x;
	p.position.y += p.velocity.y;
	p.position.z += p.velocity.z;

	p.life += 0.005f;
	if (dist < 0.15f || p.life > randRange(seed * 6, 2.0f, 4.0f))
		p.life = 0.0f;

	// Update the particle back to the global memory
	particles[id] = p;
}