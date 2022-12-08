#include "window.hpp"

namespace bork {

Window::Window(int width, int height)
{
	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);

	std::cout << false << std::endl;
	GLint flag ;
	glGetIntegerv(GL_CONTEXT_FLAGS, &flag);
	if (flag & GL_CONTEXT_FLAG_DEBUG_BIT) {
		glEnable(GL_DEBUG_OUTPUT);
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
		glDebugMessageCallback(glDebugOutput, nullptr);
		std::cout << "Here!" << std::endl;
		glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
	}

	window = glfwCreateWindow(width, height, "Flappy Bird", nullptr, nullptr);

	if (window == nullptr) {
		throw std::runtime_error("Failed to create window.");
	}

	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
	glfwSetKeyCallback(window, key_callback);
	glfwMakeContextCurrent(window);

	glewExperimental = true;
	GLenum error = glewInit();
	if (error != GLEW_OK) {
		throw std::runtime_error("Failed to initialize GLEW");
	}
}

Window::~Window()
{
	glfwDestroyWindow(window);
}

bool Window::is_closed()
{
	return glfwWindowShouldClose(window);
}

void Window::toggle_keycallback()
{
	glfwSetKeyCallback(window, key_callback);
}

void Window::update()
{
	glfwSwapBuffers(window);
	glfwPollEvents();
}

}
