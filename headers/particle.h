#ifndef SIMULATION_ARGS_H
#define SIMULATION_ARGS_H
#include "base.h"

extern int particleCount;
extern int particleSize;
extern GLuint particlesVBO, particlesVAO;

struct Particle {
    glm::vec2 position;
    glm::vec2 velocity;
    float age;
};
extern Particle* particles;


void initUniformParticles();

#endif //SIMULATION_ARGS_H
