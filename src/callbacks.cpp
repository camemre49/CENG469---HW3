#include "../headers/callbacks.h"

#include "../headers/particle.h"

void keyboard(GLFWwindow* window, int key, int scancode, int action, int mods);
void setCallbacks() {
    glfwSetKeyCallback(window, keyboard);
}


void keyboard(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (action == GLFW_PRESS) {
		switch (key) {
			case GLFW_KEY_Q:
				glfwSetWindowShouldClose(window, GLFW_TRUE);
				break;

			case GLFW_KEY_R:
				shouldDisplay = !shouldDisplay;
				break;



			case GLFW_KEY_W:
				deltaTimeMultiplier *= 1.06;
				break;
			case GLFW_KEY_S:
				deltaTimeMultiplier *= 0.94339;
				break;
			default: ;
		}
	}
}

