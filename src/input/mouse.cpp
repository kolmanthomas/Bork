#include "keyboard.h"

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (GLFW_KEY_E && action == GLFW_PRESS) {
		std::cout << "Pressed E!" << std::endl;
	}
}
