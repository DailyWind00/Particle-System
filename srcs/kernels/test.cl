__kernel void test(__global Particle* particles, float deltaTime) {
    int id = get_global_id(0);
    particles[id].position += particles[id].velocity * deltaTime;
    particles[id].velocity += (float3)(0.0f, -9.81f, 0.0f) * deltaTime;

    if (particles[id].position.y < 0.0f) {
        particles[id].position = (float3)(0.0f, 10.0f, 0.0f);
        particles[id].velocity = (float3)(0.0f, -5.0f, 0.0f);
    }
}
