// rain.cl
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
    uint seed = randRange(id, 0, particleCount) + (uint)(time * 1000.0f);

    if (p.life <= 0.0f) { // Respawn the particle
        p.position = (float3)(
            randRange(seed, -1.0f, 1.0f),
            randRange(seed * 2, 1.0f, 3.0f),
            randRange(seed * 3, -1.0f, 1.0f)
        );
        p.velocity = (float3)(0.0f, randRange(seed * 4, -0.01f, -0.025f), 0.0f);
        p.life = 1.0f;
    }

    // Basic particle behavior
    p.position += p.velocity;

    p.life = p.position.y > -1.0f;

    // Update the particle back to the global memory
    particles[id] = p;
}