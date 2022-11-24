#include "keyboard.hpp"

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_E && action == GLFW_PRESS) {
	    std::cout << "Pressed E!" << std::endl;
    }

    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
	    throw std::runtime_error("Quit!");
    }
}
