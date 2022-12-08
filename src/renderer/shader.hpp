#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <spdlog/spdlog.h>
#include <shaderc/shaderc.hpp>

#include <fstream>
#include <sstream>
#include <stdexcept>
#include <string>

#include "../utils/debugging.hpp"

namespace bork {

enum shader_type {
	shader_type_vertex,
	shader_type_fragment
};

class Shader 
{
public:
	/*
	Shader();
	Shader(shader_type st, std::string const& filepath);
	~Shader();
	*/
	static GLuint LoadShaders(const char* vertex_file_path, const char* fragment_file_path);

	std::vector<uint32_t> compile_glsl_to_spirv(shader_type st, std::string const& filepath);
	GLuint load_shader(shader_type st, std::string const& filepath);
private:
	std::string m_filepath;
	shaderc::Compiler compiler;

	shader_type m_st;
};

}

