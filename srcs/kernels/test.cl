// kernel.cl
typedef struct {
    float3 position;
    float3 velocity;
    float life;
} Particle;

uint hash(uint x) {
    x = ((x >> 16) ^ x) * 0x45d9f3b;
    x = ((x >> 16) ^ x) * 0x45d9f3b;
    x = (x >> 16) ^ x;
    return x;
}

// Linear Congruential Generator with hashed seed
float rand(uint seed) {
    seed = hash(seed);
    seed = (1103515245 * seed + 12345) & 0x7FFFFFFF; // Simple LCG
    return (float)seed / 2147483647.0f; // Normalize to [0, 1]
}

// Generate a random float between min and max
float randRange(float seed, float min, float max) {
    return min + rand(seed) * (max - min);
}

float3  randRange3(float seed, float min, float max) {
    return (float3)(
        randRange(seed, min, max),
        randRange(seed + 1, min, max),
        randRange(seed + 2, min, max)
    );
}

__kernel void update(__global Particle* particles, int particleCount, float time, float2 mouse) {
    int id = get_global_id(0); // Get the unique thread ID
    Particle p = particles[id];
    uint seed = id + (uint)(time * 1000.0f);

    if (p.life <= 0.0f) { // Respawn the particle
        p.position = randRange3(seed, -10.0f, 10.0f);
        p.velocity = (float3)(0.0f, 0.0f, 0.0f);
        p.life = 10.0f;
    }
    p.velocity.x = (mouse.x - p.position.x) * 0.9f + p.velocity.x * 0.9f;
    p.velocity.y = (mouse.y - p.position.y) * 0.9f + p.velocity.y * 0.9f;

    // Basic particle behavior
    p.position += p.velocity;
    // p.life -= 1.0f;

    // Update the particle back to the global memory
    particles[id] = p;
}