#pragma once

#include "../window.hpp"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <functional>
#include <stdexcept>

namespace bork {
namespace glfw {

class GLFWWindowImpl : public bork::base::Window {
private:
public:
	GLFWwindow* window; 
	GLFWWindowImpl(int width, int height); 
	~GLFWWindowImpl() override;
};

} // namespace closure for "window"
} // namespace closure for "bork"
