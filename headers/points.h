#ifndef SIMULATION_ARGS_H
#define SIMULATION_ARGS_H
#include "base.h"

extern int particleCount;
extern int particleSize;
extern glm::vec3* points;
extern GLuint pointsVAO, pointsVBO;

void initUniformPoints();

#endif //SIMULATION_ARGS_H
