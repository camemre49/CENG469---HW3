#include "../headers/particle.h"

#include <iostream>
#include <ostream>

int particleCount = -1;
int particleSize = -1;
GLuint particlesVBO, particlesVAO;
Particle* particles;

void initUniformParticles() {
    if (particleCount <= 0) return;

    particles = new Particle[particleCount];

    const double margin = 0.2;
    const double halfMargin = margin * 0.5;
    const double start = halfMargin - 1.0;

    double usableSpace = (2.0 - margin);

    int cols = static_cast<int>(std::ceil(std::sqrt(particleCount)));
    int rows = static_cast<int>(std::ceil(static_cast<double>(particleCount) / cols));

    double horizontalStride = usableSpace / (cols - 1);
    double verticalStride = usableSpace / (rows - 1);

    int index = 0;
    srand(time(NULL));
    for (int row = 0; row < rows && index < particleCount; row++) {
        double y = start + row * verticalStride;
        for (int col = 0; col < cols && index < particleCount; col++) {
            double x = start + col * horizontalStride;
            particles[index].position = glm::vec2(x, y);
            particles[index].velocity = glm::vec2(static_cast<float>(rand()) / static_cast<float>(RAND_MAX), static_cast<float>(rand()) / static_cast<float>(RAND_MAX));
            particles[index].age = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
            index++;
        }
    }

    // One VAO to describe structure
    glGenVertexArrays(1, &particlesVAO);
    glBindVertexArray(particlesVAO);

    // VBO with all particles
    glGenBuffers(1, &particlesVBO);
    glBindBuffer(GL_ARRAY_BUFFER, particlesVBO);
    glBufferData(GL_ARRAY_BUFFER, particleCount * sizeof(Particle), particles, GL_STATIC_DRAW);

    // Position attribute (location = 0)
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Particle), (void*)offsetof(Particle, position));
    glEnableVertexAttribArray(0);

    // Velocity attribute (location = 1)
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Particle), (void*)offsetof(Particle, velocity));
    glEnableVertexAttribArray(1);

    // Age attribute (location = 2)
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Particle), (void*)offsetof(Particle, age));
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}