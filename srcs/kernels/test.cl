__kernel void update(__global float* particles, float deltaTime) {
    int index = get_global_id(0);
    float particle = particles[index] * 7;
}