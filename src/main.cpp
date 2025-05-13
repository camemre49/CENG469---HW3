#include <iostream>
#include "../headers/simulation-args.h"
#include "../headers/window-handler.h"

void mainLoop()
{
    while (!glfwWindowShouldClose(window))
    {
        //display();
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


    mainLoop();

    return 0;
}