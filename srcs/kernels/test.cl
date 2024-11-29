// kernel.cl
typedef struct {
    float3 position;
    float3 velocity;
    float life;
} Particle;

__kernel void update(__global Particle* particles, const float deltaTime) {
    int id = get_global_id(0); // Get the unique thread ID
    Particle p = particles[id];

    // Update particle velocity (basic gravity effect)
    p.velocity.y -= deltaTime;

    // Update particle position based on velocity and deltaTime
    p.position += p.velocity * deltaTime;

    // Decrease particle life
    p.life -= 0.01f;

    // Reset if life is below zero
    if (p.life <= 0.0f) {
        p.position = (float3)(50.0f, 50.0f, 50.0f); // Reset position
        p.velocity = (float3)(0.0f, 0.0f, 0.0f);    // Reset velocity
        p.life = 5.0f;                              // Reset life
    }

    // Write the updated particle back to memory
    particles[id] = p;
}
