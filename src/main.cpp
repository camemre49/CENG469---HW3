#include <iostream>
#include "../headers/particle.h"
#include "../headers/window.h"
#include "../headers/particle.h"
#include "../headers/shaders.h"
#include "../headers/text.h"

void display();
void drawParticles();
void cleanup();

bool shouldDisplay = true;
bool shouldDisplayTexts = true;

void mainLoop()
{
    while (!glfwWindowShouldClose(window))
    {
        display();
        if (shouldDisplay) {
            glfwSwapBuffers(window);
        }
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
    initFonts(windowWidth, windowHeight);

    mainLoop();

    cleanup();
    return 0;
}

void display() {
    static float randomOriginX = 0.0f;
    static float randomOriginY = 0.0f;
    static float deltaTime = 0.0f;
    if (originPosition.x <= -1.0f) {
        // Calculate delta time
        static float lastTime = glfwGetTime();
        float currentTime = glfwGetTime();
        deltaTime = currentTime - lastTime;
        lastTime = currentTime;

        // Static variables to store randomOrigin and control its update rate
        static float originUpdateInterval = 10.0f; // seconds
        static float timeSinceOriginUpdate = 0.0f;
        static float randomOriginMultiplier = 0.8f;
        // Accumulate time
        timeSinceOriginUpdate += deltaTime;
        if (timeSinceOriginUpdate >= originUpdateInterval) {
            // Update origin only once per interval
            randomOriginX = static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * randomOriginMultiplier - randomOriginMultiplier/2;
            randomOriginY = static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * randomOriginMultiplier - randomOriginMultiplier/2;
            timeSinceOriginUpdate = 0.0f;
        }
    }

    if (shouldDisplay) {
        // Update particles with compute shader
        glBlendFunc(GL_ONE, GL_ONE);
        glUseProgram(computeProgram);
        glUniform1f(glGetUniformLocation(computeProgram, "deltaTime"), deltaTime * deltaTimeMultiplier);
        glUniform1f(glGetUniformLocation(computeProgram, "positionMultiplier"), (static_cast<float>(rand()) / static_cast<float>(RAND_MAX)));
        // IF origin is not defined yet, set randomly
        if (originPosition.x <= -1.0f) {
            glUniform2f(glGetUniformLocation(computeProgram, "origin"),randomOriginX, randomOriginY);
        }
        else {
            glUniform2f(glGetUniformLocation(computeProgram, "origin"),originPosition.x, originPosition.y);
        }
        glUniform1i(glGetUniformLocation(computeProgram, "currentNumOfAttractors"), currentNumOfAttractors);
        glUniform1f(glGetUniformLocation(computeProgram, "attractorMass"), attractorMass);
        glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, particlesVBO);
        glDispatchCompute((particleCount + 127) / 128, 1, 1); // 128 particles per work group

        // Add memory barrier to ensure compute shader finishes before rendering
        glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT | GL_VERTEX_ATTRIB_ARRAY_BARRIER_BIT);

        // Clear screen
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        drawParticles();


        if (shouldDisplayTexts) {
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            displayTexts();
        }
    }
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