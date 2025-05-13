#version 430 core

struct Particle {
    vec2 position;
    vec2 velocity;
    float age;
};

layout(std430, binding = 0) buffer Particles {
    Particle particles[];
};

uniform float deltaTime;
vec2 boundsMin = vec2(-1.0, -1.0);
vec2 boundsMax = vec2(1.0, 1.0);

layout(local_size_x = 128, local_size_y = 1, local_size_z = 1) in;

void main() {
    uint idx = gl_GlobalInvocationID.x;
    if (idx >= particles.length()) return;

    // Update position
    particles[idx].position += particles[idx].velocity * deltaTime * 0.1;

    // Simple boundary checking
    if (particles[idx].position.x < boundsMin.x || particles[idx].position.x > boundsMax.x) {
        particles[idx].velocity.x *= -1.0;
    }
    if (particles[idx].position.y < boundsMin.y || particles[idx].position.y > boundsMax.y) {
        particles[idx].velocity.y *= -1.0;
    }

    // Update age
    particles[idx].age = particles[idx].age - 0.003;
    if(particles[idx].age < 0) {
        particles[idx].age = 1.0f;
    }
}