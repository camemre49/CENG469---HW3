#include <iostream>
#include "../headers/particle.h"
#include "../headers/window.h"
#include "../headers/particle.h"
#include "../headers/shaders.h"

void display();
void mainLoop()
{
    while (!glfwWindowShouldClose(window))
    {
        display();
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

    return 0;
}

void drawParticles();
void display() {
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