#pragma once

#include <stdexcept>

class RuntimeError : public std::runtime_error
{
public:
	RuntimeError(const std::string& msg, const char* file, const char* func, int line)
		: std::runtime_error(msg)
	{
		full_msg = "Traceback (internal exception API)\n"
			"File \"" + std::string(file) + "\", line " + std::to_string(line) + ", in " + std::string(func) + "\n\t" 
			+ "Diagnostic: " + msg;
	}

	const char* what() const throw()
	{
		return full_msg.c_str();
	}
private:
	std::string full_msg;
};

#define RUNTIME_ERROR(msg) RuntimeError(msg, __FILE__, __func__, __LINE__)
