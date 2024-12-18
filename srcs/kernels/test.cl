// kernel.cl
typedef struct {
    float3 position;
    float3 velocity;
    float life;
} Particle;

__kernel void update(__global Particle* particles) {
    int id = get_global_id(0); // Get the unique thread ID
    Particle p = particles[id];

    if (p.life <= 0.0f) { // Respawn the particle
        p.position = (float3)(id, 5.0f, 0.0f);
        p.velocity = (float3)(0.0f, 1.0f, 0.0f);
        p.life = 10.0f;
    }

    p.position.y += p.velocity.y;

    particles[id] = p;
}