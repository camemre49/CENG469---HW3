#version 430 core

struct Particle {
    vec4 position;
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
    vec2 vel = particles[idx].velocity * deltaTime * 0.5;
    particles[idx].position.x += vel.x;
    particles[idx].position.y += vel.y;

    // Simple boundary checking
    if (particles[idx].position.x < boundsMin.x || particles[idx].position.x > boundsMax.x) {
        particles[idx].velocity.x *= -1.0;
    }
    if (particles[idx].position.y < boundsMin.y || particles[idx].position.y > boundsMax.y) {
        particles[idx].velocity.y *= -1.0;
    }

    // Update age
    particles[idx].age = particles[idx].age - 0.01;
    if(particles[idx].age < 0) {
        particles[idx].position.x = particles[idx].position.z;
        particles[idx].position.y = particles[idx].position.w;
        particles[idx].position.z *= 0.8;
        particles[idx].position.w *= 0.8;
        particles[idx].age = 1.0f;
    }
}