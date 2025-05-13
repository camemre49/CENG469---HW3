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
            particles[index].velocity = glm::vec2(
                (static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * 2) - 1.0f,
                (static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * 2) - 1.0f
                );
            particles[index].age = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
            index++;
        }
    }

    // Create SSBO for compute shader
    glGenBuffers(1, &particlesVBO);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, particlesVBO);
    glBufferData(GL_SHADER_STORAGE_BUFFER, particleCount * sizeof(Particle), particles, GL_DYNAMIC_DRAW);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);

    // VAO for rendering
    glGenVertexArrays(1, &particlesVAO);
    glBindVertexArray(particlesVAO);

    // Bind the same buffer but as ARRAY_BUFFER for rendering
    glBindBuffer(GL_ARRAY_BUFFER, particlesVBO);

    // Position attribute (location = 0)
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Particle), (void*)offsetof(Particle, position));
    glEnableVertexAttribArray(0);

    // Velocity attribute (location = 1)
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Particle), (void*)offsetof(Particle, velocity));
    glEnableVertexAttribArray(1);

    // Age attribute (location = 2)
    glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, sizeof(Particle), (void*)offsetof(Particle, age));
    glEnableVertexAttribArray(2);

    glBindVertexArray(0);
}