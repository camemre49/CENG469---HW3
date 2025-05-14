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

// Attractors:
uniform int currentNumOfAttractors;
// vec3(x, y, strength)
uniform vec3 attractors[12]; // Maximum number of attractors is 100 for now

// Reinitialize parameters
uniform float positionMultiplier = 0.8;
uniform vec2 randomOrigin;
float attractorFactor = 0.5;

layout(local_size_x = 128, local_size_y = 1, local_size_z = 1) in;

void main() {
    uint idx = gl_GlobalInvocationID.x;
    if (idx >= particles.length()) return;

    vec2 vel = particles[idx].velocity.xy;

    particles[idx].position.xy += vel * deltaTime;

    for(int i = 0; i < currentNumOfAttractors; i++) {
        vec2 dist = (attractors[i].xy - particles[idx].position.xy) * 2;
        vel += deltaTime * deltaTime * attractors[i].z * normalize(dist) / (dot(dist, dist) + 10.0);
    }
    if (length(vel) > attractorFactor) {
        vel = normalize(vel) * attractorFactor;
    }
    particles[idx].velocity.xy = vel;

    // Simple boundary checking
    if (particles[idx].position.x < boundsMin.x || particles[idx].position.x > boundsMax.x) {
        particles[idx].velocity.x *= -1.0;
    }
    if (particles[idx].position.y < boundsMin.y || particles[idx].position.y > boundsMax.y) {
        particles[idx].velocity.y *= -1.0;
    }

    // Update age
    particles[idx].age -= 0.001 * deltaTime;
    if(particles[idx].age < 0) {
        // Uniform
        //particles[idx].position.x = particles[idx].position.z;
        //particles[idx].position.y = particles[idx].position.w;

        // Random origin
        particles[idx].position.xy = randomOrigin.xy;
        particles[idx].age = 1.0f;
    }
}