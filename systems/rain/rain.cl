// rain.cl
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

__kernel void update(__global Particle* particles, int particleCount, float time, float2 mouse) {
    uint id = get_global_id(0); // Get the unique thread ID
    Particle p = particles[id];
    uint seed = randRange(id, 0, particleCount) + (uint)(time * 1000.0f);

    if (p.life <= 0.0f) { // Respawn the particle
        p.position.x = randRange(seed, -1.0f, 1.0f);
        p.position.y = randRange(seed * 2, 1.0f, 3.0f);
        p.position.z = randRange(seed * 3, -1.0f, 1.0f);

        p.velocity.x = 0.0f;
        p.velocity.y = randRange(seed * 4, -0.01f, -0.025f);
        p.velocity.z = 0.0f;
        
        p.life = 1.0f;
    }

    // Wind
    p.velocity.x += randRange(seed * 5, -0.00005f, 0.00005f);

    // Particle physics
    p.position.x += p.velocity.x * p.life;
    p.position.y += p.velocity.y * p.life;
    p.position.z += p.velocity.z * p.life;

    p.life += 0.005f;
    if (p.position.y < -1.0f)
        p.life = 0.0f;

    // Update the particle back to the global memory
    particles[id] = p;
}