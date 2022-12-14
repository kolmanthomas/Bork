#include "keyboard.hpp"

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_E && action == GLFW_PRESS) {
    }

    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
	    throw std::runtime_error("Quit!");
    }
}
