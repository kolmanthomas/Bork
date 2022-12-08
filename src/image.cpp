#include "image.hpp"

#include <iostream>

namespace bork {

std::vector<unsigned char> load_binary_file(std::string const& filepath)
{
	std::cout << "Here!" << std::endl;
	std::ifstream file(filepath, std::ios::binary | std::ios::ate);

	if (!file.is_open()) {
		throw std::runtime_error("RUNTIME ERROR: Cannot open file: " + filepath);
	} 

	size_t len = static_cast<size_t>(file.tellg());
	file.seekg(0);
	std::vector<unsigned char> buffer(len);
	buffer.insert(buffer.begin(), 
		std::istreambuf_iterator<char>(file), 
		std::istreambuf_iterator<char>()
	);

	return buffer;
}

uint32_t convert_bytes_to_int32(std::vector<unsigned char>::iterator start)
{
	if (std::endian::native == std::endian::big) {
		return static_cast<uint32_t>(*start) << 24 |
		       static_cast<uint32_t>(*(start + 1)) << 16 |
		       static_cast<uint32_t>(*(start + 2)) << 8 |
		       static_cast<uint32_t>(*(start + 3));
	} else {
		return static_cast<uint32_t>(*start) << 0 |
		       static_cast<uint32_t>(*(start + 1)) << 8 |
		       static_cast<uint32_t>(*(start + 2)) << 16 |
		       static_cast<uint32_t>(*(start + 3)) << 24;
	}
}


BMP loadBMP(std::string const& filepath)
{
	std::vector<unsigned char> image = load_binary_file(filepath);

	if (image.size() < 54 || image[0] != 'B' || image[1] != 'M') {
		throw std::runtime_error("Not a BMP file!");
	}

	uint32_t size = convert_bytes_to_int32(image.begin() + 0x22);
	uint32_t data_start = convert_bytes_to_int32(image.begin() + 0x0A);

	std::cout << image.size() << std::endl;
	std::cout << size << std::endl;

	return BMP {
		.width = convert_bytes_to_int32(image.begin() + 0x12),
		.height = convert_bytes_to_int32(image.begin() + 0x16),
		.data = std::vector<unsigned char>(image.begin() + 54, image.begin() + data_start + size)
	};
}

}
