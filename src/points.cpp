#include "../headers/points.h"

int particleCount = -1;
int particleSize = -1;
glm::vec3* points;
GLuint pointsVAO, pointsVBO;

void initUniformPoints() {
    if (particleCount <= 0) return;

    points = new glm::vec3[particleCount];

    const double margin = 0.2;
    const double halfMargin = margin * 0.5;
    const double start = halfMargin - 1.0;

    double usableSpace = (2.0 - margin);

    int cols = static_cast<int>(std::ceil(std::sqrt(particleCount)));
    int rows = static_cast<int>(std::ceil(static_cast<double>(particleCount) / cols));

    double horizontalStride = usableSpace / (cols - 1);
    double verticalStride = usableSpace / (rows - 1);

    int index = 0;
    for (int row = 0; row < rows && index < particleCount; row++) {
        double y = start + row * verticalStride;
        for (int col = 0; col < cols && index < particleCount; col++) {
            double x = start + col * horizontalStride;
            points[index++] = glm::vec3(x, y, -1.0f);
        }
    }

    // Initialize VAO and VBO
    glGenVertexArrays(1, &pointsVAO);
    glGenBuffers(1, &pointsVBO);

    glBindVertexArray(pointsVAO);
    glBindBuffer(GL_ARRAY_BUFFER, pointsVBO);
    glBufferData(GL_ARRAY_BUFFER, particleCount * sizeof(glm::vec3), points, GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}