#include "glfw_window.hpp"

namespace bork {
namespace glfw {

GLFWWindowImpl::GLFWWindowImpl(int width, int height)
{
	window = glfwCreateWindow(width, height, "Flappy Bird", nullptr, nullptr);

	if (window == nullptr) {
		throw std::runtime_error("Failed to create window.");
	}

	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
	{
	});
	
	glfwMakeContextCurrent(window);

	glewExperimental = true;
	GLenum error = glewInit();
	if (error != GLEW_OK) {
		throw std::runtime_error("Failed to initialize GLEW");
	}
}

GLFWWindowImpl::~GLFWWindowImpl()
{
	glfwDestroyWindow(window);
}

} // namespace closure for "glfw"
} // namespace closure for "bork"

