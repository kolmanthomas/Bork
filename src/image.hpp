#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <bit>
#include <fstream>
#include <vector>

namespace bork {

typedef struct BMP_header {
	uint32_t width;	
	uint32_t height;
	std::vector<unsigned char> data;
} BMP;

BMP loadBMP(std::string const& imagepath);
std::vector<unsigned char> load_binary_file(std::string const& filepath);



}
