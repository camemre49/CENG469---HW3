#include <iostream>
#include "../headers/particle.h"
#include "../headers/window.h"
#include "../headers/particle.h"
#include "../headers/shaders.h"

void display();
void drawParticles();
void cleanup();

bool shouldDisplay = true;


void mainLoop()
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_ONE, GL_ONE);
    while (!glfwWindowShouldClose(window))
    {
        if (shouldDisplay) {
            display();
        }
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

int main(const int argc, const char *argv[]) {
    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " <int1> <int2>" << std::endl;
        return 1;
    }
    particleCount = atoi(argv[1]);
    particleSize = atoi(argv[2]);
    initWindow();
    setCallbacks();
    initShaders();
    initUniformParticles();

    mainLoop();

    cleanup();
    return 0;
}

void display() {
    // Calculate delta time
    static float lastTime = glfwGetTime();
    float currentTime = glfwGetTime();
    float deltaTime = currentTime - lastTime;
    lastTime = currentTime;

    // Update particles with compute shader
    glUseProgram(computeProgram);
    glUniform1f(glGetUniformLocation(computeProgram, "deltaTime"), deltaTime);
    glUniform1f(glGetUniformLocation(computeProgram, "positionMultiplier"), (static_cast<float>(rand()) / static_cast<float>(RAND_MAX)));
    glUniform2f(glGetUniformLocation(computeProgram, "randomOrigin"),
        (static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * 2 - 1),
        (static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * 2 - 1)
        );
    glUniform1i(glGetUniformLocation(computeProgram, "currentNumOfAttractors"), currentNumOfAttractors);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, particlesVBO);
    glDispatchCompute((particleCount + 127) / 128, 1, 1); // 128 particles per work group

    // Add memory barrier to ensure compute shader finishes before rendering
    glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT | GL_VERTEX_ATTRIB_ARRAY_BARRIER_BIT);

    // Clear screen
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    drawParticles();
}

void drawParticles() {
    glClearColor(0, 0, 0 , 1);
    glClearDepth(1.0f);
    glClearStencil(0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glUseProgram(particleProgram);
    glBindVertexArray(particlesVAO);

    glPointSize(static_cast<float>(particleSize));
    glDrawArrays(GL_POINTS, 0, particleCount);

    glBindVertexArray(0);
}

void cleanup() {
    glDeleteVertexArrays(1, &particlesVAO);
    glDeleteBuffers(1, &particlesVBO);
    delete[] particles;
}