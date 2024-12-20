// random_utils.cl
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