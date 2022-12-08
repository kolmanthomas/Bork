#pragma once

#include "utils/debugging.hpp"
#include "input/keyboard.hpp"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <memory>

namespace bork {

class Window {
public:
	Window(int width, int height);
	~Window();

	bool is_closed();
	void toggle_keycallback();
	void update();
private:
	GLFWwindow* window;
};

}
