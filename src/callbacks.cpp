#include "../headers/callbacks.h"
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
				shouldDisplay = true;
				break;
			default: ;
		}
	}
}

