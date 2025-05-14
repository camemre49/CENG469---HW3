#ifndef SIMULATION_ARGS_H
#define SIMULATION_ARGS_H
#include <vector>

#include "base.h"

extern int particleCount;
extern int particleSize;
extern GLuint particlesVBO, particlesVAO;
extern int currentNumOfAttractors;
extern std::vector<glm::vec3> attractorPoints;
extern float deltaTimeMultiplier;

struct Particle {
    glm::vec4 position;
    glm::vec2 velocity;
    float age;
    float _pad1;     // 4 bytes to align struct size to 24 bytes
};
extern Particle* particles;


void initUniformParticles();

#endif //SIMULATION_ARGS_H
