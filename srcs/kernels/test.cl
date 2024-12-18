// kernel.cl
typedef struct {
    float3 position;
    float3 velocity;
    float life;
} Particle;

__kernel void update(__global Particle* particles, const float deltaTime) {
    int id = get_global_id(0); // Get the unique thread ID
    Particle p = particles[id];

    if (p.life <= 0.0f) { // Respawn the particle
        p.position = (float3)(1.0f, 2.0f, 3.0f);
        p.velocity = (float3)(4.0f, 5.0f, 6.0f);
        p.life = 10.0f;
    }

    p.position.x = id;

    particles[id] = p;
}