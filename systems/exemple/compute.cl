// exemple.cl

// Choose the type of particle you want to use

// [Optimise data for huge particle count] : [Recommended]
// typedef struct {
//     struct {
//         float x;
//         float y;
//         float z;
//     } position;

//     struct {
//         float x;
//         float y;
//         float z;
//     } velocity;

//     float life;
// } Particle;

// [Can be used for small particle count] 
// typedef struct {
// 	float3 position;
// 	float3 velocity;
// 	float life;
// } Particle;

__kernel void update(__global Particle* particles, int particleCount, float time, float2 center) {
	uint id = get_global_id(0); // Get the unique thread ID
	Particle p = particles[id];

	if (p.life <= 0.0f) { // Respawn the particle [Do math here]
		p.position.x = 0.0f;
		p.position.y = 0.0f;
		p.position.z = 0.0f;

		p.velocity.x = 0.0f;
		p.velocity.y = 0.0f;
		p.velocity.z = 0.0f;
		
		p.life = 1.0f;
	}

	// [Do math here]

	// Particle physics
	p.position.x += p.velocity.x;
	p.position.y += p.velocity.y;
	p.position.z += p.velocity.z;

	// Update the particle back to the global memory
	particles[id] = p;
}
