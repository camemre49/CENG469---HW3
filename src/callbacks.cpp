#include "../headers/callbacks.h"

#include <iostream>
#include <ostream>

#include "../headers/particle.h"
#include "../headers/shaders.h"

void keyboard(GLFWwindow* window, int key, int scancode, int action, int mods);
void reshape(GLFWwindow* window, int width, int height);
void mouseScroll(GLFWwindow* window, double xOffset, double yOffset);
void mouseButton(GLFWwindow* window, int button, int action, int mods);
void setCallbacks() {
    glfwSetKeyCallback(window, keyboard);
	glfwSetFramebufferSizeCallback(window, reshape);
	glfwSetScrollCallback(window, mouseScroll);
	glfwSetMouseButtonCallback(window, mouseButton);
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
			case GLFW_KEY_F:
				static bool isFullScreen = false;
				if (!isFullScreen) {
					// Save current window position
					if (!windowPosX) {
						glfwGetWindowPos(window, &windowPosX, &windowPosY);
					}

					// Get primary monitor and video mode
					GLFWmonitor* monitor = glfwGetPrimaryMonitor();
					const GLFWvidmode* mode = glfwGetVideoMode(monitor);

					// Set full screen
					glfwSetWindowMonitor(window, monitor, 0, 0, mode->width, mode->height, mode->refreshRate);
					isFullScreen = true;
				} else {
					// Return to windowed mode
					glfwSetWindowMonitor(window, NULL, windowPosX, windowPosY, windowWidth, windowHeight, 0);
					isFullScreen = false;
				}
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

void reshape(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

constexpr float scrollThreshold = 2.0f;
void mouseScroll(GLFWwindow* window, double xoffset, double yoffset) {
	static double accumulatedScroll = 0.0;
	accumulatedScroll += yoffset;
	std::cout << accumulatedScroll << std::endl;
	if (accumulatedScroll >= scrollThreshold) {
		if (attractorMass < 100.0f) {
			attractorMass += 10.0f;
		}
		accumulatedScroll -= scrollThreshold;
	}
	else if (accumulatedScroll <= -scrollThreshold) {
		if (attractorMass > 0.0f) {
			attractorMass -= 10.0f;
		}
		accumulatedScroll += scrollThreshold;
	}
}

void mouseButton(GLFWwindow* window, int button, int action, int mods) {
	if (action == GLFW_PRESS) {
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);

		// Convert to OpenGL normalized device coords (-1 to 1)
		int width, height;
		glfwGetWindowSize(window, &width, &height);
		float xNDC = (2.0f * xpos) / width - 1.0f;
		float yNDC = 1.0f - (2.0f * ypos) / height;

		if (button == GLFW_MOUSE_BUTTON_LEFT) {
			if (currentNumOfAttractors < 12) {
				attractorPoints.push_back(glm::vec3(xNDC, yNDC, attractorMass));
				currentNumOfAttractors++;
			}
		}
		else if (button == GLFW_MOUSE_BUTTON_RIGHT) {
			if (!attractorPoints.empty()) {
				attractorPoints.pop_back();
				currentNumOfAttractors--;
			}
		}

		std::cout << currentNumOfAttractors << std::endl;
		std::cout << attractorMass << std::endl;

		// Update uniform
		glUseProgram(computeProgram);
		glUniform3fv(glGetUniformLocation(computeProgram, "attractors"),
					 currentNumOfAttractors,
					 glm::value_ptr(attractorPoints[0]));
	}
}

