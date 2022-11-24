#include "shader.hpp"

#include <iostream>

namespace nmn {

/*
GLuint Shader::LoadShaders(const char * vertex_file_path,const char * fragment_file_path)
{

	// Create the shaders
	GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	// Read the Vertex Shader code from the file
	std::string VertexShaderCode;
	std::ifstream VertexShaderStream(vertex_file_path, std::ios::in);
	if(VertexShaderStream.is_open()){
		std::stringstream sstr;
		sstr << VertexShaderStream.rdbuf();
		VertexShaderCode = sstr.str();
		VertexShaderStream.close();
	}else{
		printf("Impossible to open %s. Are you in the right directory ? Don't forget to read the FAQ !\n", vertex_file_path);
		getchar();
		return 0;
	}

	// Read the Fragment Shader code from the file
	std::string FragmentShaderCode;
	std::ifstream FragmentShaderStream(fragment_file_path, std::ios::in);
	if(FragmentShaderStream.is_open()){
		std::stringstream sstr;
		sstr << FragmentShaderStream.rdbuf();
		FragmentShaderCode = sstr.str();
		FragmentShaderStream.close();
	}

	GLint Result = GL_FALSE;
	int InfoLogLength;

	// Compile Vertex Shader
	printf("Compiling shader : %s\n", vertex_file_path);
	char const * VertexSourcePointer = VertexShaderCode.c_str();
	glShaderSource(VertexShaderID, 1, &VertexSourcePointer , NULL);
	glCompileShader(VertexShaderID);

	// Check Vertex Shader
	glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if ( InfoLogLength > 0 ){
		std::vector<char> VertexShaderErrorMessage(InfoLogLength+1);
		glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
		printf("%s\n", &VertexShaderErrorMessage[0]);
	}

	// Compile Fragment Shader
	printf("Compiling shader : %s\n", fragment_file_path);
	char const * FragmentSourcePointer = FragmentShaderCode.c_str();
	glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer , NULL);
	glCompileShader(FragmentShaderID);

	// Check Fragment Shader
	glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if ( InfoLogLength > 0 ){
		std::vector<char> FragmentShaderErrorMessage(InfoLogLength+1);
		glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
		printf("%s\n", &FragmentShaderErrorMessage[0]);
	}

	// Link the program
	printf("Linking program\n");
	GLuint ProgramID = glCreateProgram();
	glAttachShader(ProgramID, VertexShaderID);
	glAttachShader(ProgramID, FragmentShaderID);
	glLinkProgram(ProgramID);

	// Check the program
	glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
	glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if ( InfoLogLength > 0 ){
		std::vector<char> ProgramErrorMessage(InfoLogLength+1);
		glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
		printf("%s\n", &ProgramErrorMessage[0]);
	}
	
	glDetachShader(ProgramID, VertexShaderID);
	glDetachShader(ProgramID, FragmentShaderID);
	
	glDeleteShader(VertexShaderID);
	glDeleteShader(FragmentShaderID);

	return ProgramID;
}
*/

std::vector<uint32_t> Shader::compile_glsl_to_spirv(shader_type st, std::string const& filepath)
{
	std::ifstream file(filepath, std::ios::ate);

	if (!file.is_open()) {
		throw std::runtime_error("ERROR: Cannot open file: " + filepath);
	} 

	size_t file_len = static_cast<size_t>(file.tellg());
	std::vector<char> spirv_buffer(file_len);
	file.seekg(0);
	file.read(spirv_buffer.data(), file_len);	

	shaderc_shader_kind sk;
	switch (st) {
		case shader_type_vertex: 
			sk = shaderc_vertex_shader;
			break;
		case shader_type_fragment: 
			sk = shaderc_fragment_shader; 
			break;
	}
	shaderc::SpvCompilationResult spirv_file = compiler.CompileGlslToSpv(spirv_buffer.data(), spirv_buffer.size(), sk, "vertex_shader.vert");

	// Check compilation status, and in case of failure, terminate with error message 
	shaderc_compilation_status glsl_to_spv_compile_status = spirv_file.GetCompilationStatus();
	std::string error;
	switch (glsl_to_spv_compile_status) {
		case shaderc_compilation_status_success:
			break;
		case shaderc_compilation_status_invalid_stage:
			error = "Invalid stage";
			[[fallthrough]];
		case shaderc_compilation_status_compilation_error:
			error = "Compilation error";
			[[fallthrough]];
		case shaderc_compilation_status_internal_error:
			error = "Internal error";
			[[fallthrough]];
		case shaderc_compilation_status_null_result_object:
			error = "Null result object";
			[[fallthrough]];
		case shaderc_compilation_status_invalid_assembly:
			error = "Invalid assembly";
			[[fallthrough]];
		case shaderc_compilation_status_validation_error:
			error = "Validation error";
			[[fallthrough]];
		case shaderc_compilation_status_transformation_error:
			error = "Transformation error";
			[[fallthrough]];
		case shaderc_compilation_status_configuration_error:
			error = "Configuration error";
			[[fallthrough]];
		default:
			throw std::runtime_error("Shader compile error: " + error);
	}

	return {spirv_file.cbegin(), spirv_file.cend()};
}

GLuint Shader::load_shader(shader_type st, std::string const& filepath)
{
	GLenum pname;
	switch (st) {
		case shader_type_vertex: 
			pname = GL_VERTEX_SHADER;
			break;
		case shader_type_fragment: 
			pname = GL_FRAGMENT_SHADER;
			break;
	}

	std::vector<uint32_t> vertex_spirv = compile_glsl_to_spirv(st, filepath);	
	std::cout << "Vertex spirv size: " << vertex_spirv.size();
	GLuint vertex_shader = glCreateShader(pname);
	glShaderBinary(1, &vertex_shader, GL_SHADER_BINARY_FORMAT_SPIR_V, vertex_spirv.data(), vertex_spirv.size() * sizeof(uint32_t));
	glSpecializeShader(vertex_shader, "main", 0, nullptr, nullptr); 

	GLint compile_status;
	glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &compile_status);
	if (compile_status == GL_FALSE) {
		GLint maxLength = 0;
		glGetShaderiv(vertex_shader, GL_INFO_LOG_LENGTH, &maxLength);
		std::vector<GLchar> infoLog(maxLength);
		glGetShaderInfoLog(vertex_shader, maxLength, &maxLength, infoLog.data());
		
		std::cout << infoLog.data() << std::endl;

		// We don't need the shader anymore.
		glDeleteShader(vertex_shader);

		throw std::runtime_error("ERROR: Shader cannot compile: " + filepath);
	}

	return vertex_shader; 
	
}


}

