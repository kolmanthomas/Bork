#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <Eigen/Dense>
#include <Eigen/Geometry>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>
#include <iomanip>
#include <stdexcept>

#include "glfw/glfw_window.hpp"
#include "image.hpp"
#include "renderer/shader.hpp"
#include "math/matrix_transforms.hpp"
#include "math/trigonometry.hpp"

using namespace Eigen;

class Main 
{
public:
	void run() 
	{
		init();
		main_loop();
	}

	~Main()
	{
		glfwTerminate();
	}
private:
	const std::string vs_path = "../../src/shaders/vs.vert";
	const std::string fs_path = "../../src/shaders/fs.frag";

	GLuint programID;

	void main_loop() 
	{
		bork::glfw::GLFWWindowImpl window(1024, 768);

		glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

		GLuint VertexArrayID;
		glGenVertexArrays(1, &VertexArrayID);
		glBindVertexArray(VertexArrayID);

		bork::Shader shader;
		programID = shader.LoadShaders(vs_path.data(), fs_path.data());

		std::string path = "../../assets/sample_640×426.bmp";
		bork::BMP texture = bork::loadBMP(path);

		GLuint textureID;
		glGenTextures(1, &textureID);
		glBindTexture(GL_TEXTURE_2D, textureID);
		
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texture.width, texture.height, 0, GL_BGR, GL_UNSIGNED_BYTE, texture.data.data());

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		/*
		programID = glCreateProgram();
		nmn::Shader shader;
		GLuint vertex_shader = shader.load_shader(nmn::shader_type_vertex, vs_path); 
		GLuint fragment_shader = shader.load_shader(nmn::shader_type_fragment, fs_path); 

		glAttachShader(programID, vertex_shader);
		glAttachShader(programID, fragment_shader);
		glLinkProgram(programID); 
		GLint isLinked = 0;
		glGetProgramiv(programID, GL_LINK_STATUS, (int *)&isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(programID, maxLength, &maxLength, &infoLog[0]);
			
			// We don't need the program anymore.
			// Don't leak shaders either.

		}
		glDetachShader(programID, vertex_shader);
		glDetachShader(programID, fragment_shader);
		*/



		// Components of the model matrix

		Matrix<float, 36, 3, RowMajor> vbd {
			{-1.0f,-1.0f,-1.0f}, // triangle 1 : begin
			{-1.0f,-1.0f, 1.0f},
			{-1.0f, 1.0f, 1.0f}, // triangle 1 : end
			{1.0f, 1.0f,-1.0f}, // triangle 2 : begin
			{-1.0f,-1.0f,-1.0f},
			{-1.0f, 1.0f,-1.0f}, // triangle 2 : end
			{1.0f,-1.0f, 1.0f},
			{-1.0f,-1.0f,-1.0f},
			{1.0f,-1.0f,-1.0f},
			{1.0f, 1.0f,-1.0f},
			{1.0f,-1.0f,-1.0f},
			{-1.0f,-1.0f,-1.0f},
			{-1.0f,-1.0f,-1.0f},
			{-1.0f, 1.0f, 1.0f},
			{-1.0f, 1.0f,-1.0f},
			{1.0f,-1.0f, 1.0f},
			{-1.0f,-1.0f, 1.0f},
			{-1.0f,-1.0f,-1.0f},
			{-1.0f, 1.0f, 1.0f},
			{-1.0f,-1.0f, 1.0f},
			{1.0f,-1.0f, 1.0f},
			{1.0f, 1.0f, 1.0f},
			{1.0f,-1.0f,-1.0f},
			{1.0f, 1.0f,-1.0f},
			{1.0f,-1.0f,-1.0f},
			{1.0f, 1.0f, 1.0f},
			{1.0f,-1.0f, 1.0f},
			{1.0f, 1.0f, 1.0f},
			{1.0f, 1.0f,-1.0f},
			{-1.0f, 1.0f,-1.0f},
			{1.0f, 1.0f, 1.0f},
			{-1.0f, 1.0f,-1.0f},
			{-1.0f, 1.0f, 1.0f},
			{1.0f, 1.0f, 1.0f},
			{-1.0f, 1.0f, 1.0f},
			{1.0f,-1.0f, 1.0f}
		};


		static const GLfloat uv[] = {
			0.000059f, 1.0f-0.000004f,
			0.000103f, 1.0f-0.336048f,
			0.335973f, 1.0f-0.335903f,
			1.000023f, 1.0f-0.000013f,
			0.667979f, 1.0f-0.335851f,
			0.999958f, 1.0f-0.336064f,
			0.667979f, 1.0f-0.335851f,
			0.336024f, 1.0f-0.671877f,
			0.667969f, 1.0f-0.671889f,
			1.000023f, 1.0f-0.000013f,
			0.668104f, 1.0f-0.000013f,
			0.667979f, 1.0f-0.335851f,
			0.000059f, 1.0f-0.000004f,
			0.335973f, 1.0f-0.335903f,
			0.336098f, 1.0f-0.000071f,
			0.667979f, 1.0f-0.335851f,
			0.335973f, 1.0f-0.335903f,
			0.336024f, 1.0f-0.671877f,
			1.000004f, 1.0f-0.671847f,
			0.999958f, 1.0f-0.336064f,
			0.667979f, 1.0f-0.335851f,
			0.668104f, 1.0f-0.000013f,
			0.335973f, 1.0f-0.335903f,
			0.667979f, 1.0f-0.335851f,
			0.335973f, 1.0f-0.335903f,
			0.668104f, 1.0f-0.000013f,
			0.336098f, 1.0f-0.000071f,
			0.000103f, 1.0f-0.336048f,
			0.000004f, 1.0f-0.671870f,
			0.336024f, 1.0f-0.671877f,
			0.000103f, 1.0f-0.336048f,
			0.336024f, 1.0f-0.671877f,
			0.335973f, 1.0f-0.335903f,
			0.667969f, 1.0f-0.671889f,
			1.000004f, 1.0f-0.671847f,
			0.667979f, 1.0f-0.335851f
		};
		/*
		Matrix<GLfloat, 3, 3> vbd {
			{-1.0f, 0.0f, 1.0f},
			{-1.0f, 1.0f, -1.0f},
			{0.0f, 0.0f, 0.0f}
		};
		*/

		GLuint vertexbuffer;
		glGenBuffers(1, &vertexbuffer);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * vbd.size(), vbd.data(), GL_STATIC_DRAW);

		GLuint matrixID = glGetUniformLocation(programID, "MVP");

		GLuint colorbuffer;
		glGenBuffers(1, &colorbuffer);
		glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(uv), &uv[0], GL_STATIC_DRAW);

		GLfloat fov = 90;
		Transform<GLfloat, 3, Affine> model = bork::math::model_matrix(0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f);
		Transform<GLfloat, 3, Affine> view = bork::math::look_at_matrix(
				Vector<GLfloat, 3> {4, 3, 3}, 
				Vector<GLfloat, 3> {0, 0, 0},
				Vector<GLfloat, 3> {0, 1, 0}
		);
		Transform<GLfloat, 3, Projective> projection = bork::math::perspective_matrix(
			bork::math::degrees_to_radians(fov),
			static_cast<GLfloat> (1024) / static_cast<GLfloat> (768), 
			static_cast<GLfloat> (0.1), 
			static_cast<GLfloat> (100)	
		);

		Matrix<GLfloat, 4, 4> mvp = projection.matrix() * view.matrix() * model.matrix();
 
		while (glfwWindowShouldClose(window.window) == 0) {
			// Clear the screen
			glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			// Use our shader
			glUseProgram(programID);
			glUniformMatrix4fv(matrixID, 1, GL_FALSE, mvp.data());

			// 1rst attribute buffer : vertices
			glEnableVertexAttribArray(0);
			glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
			glVertexAttribPointer(
				0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
				3,                  // size
				GL_FLOAT,           // type
				GL_FALSE,           // normalized?
				0,                  // stride
				(void*)0            // array buffer offset
			);

			glEnableVertexAttribArray(1);
			glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
			glVertexAttribPointer(
				1,
				3,
				GL_FLOAT,
				GL_FALSE,
				0,
				(void*)0
			);
		
			// Draw the triangle !
			glDrawArrays(GL_TRIANGLES, 0, 12*3); // 3 indices starting at 0 -> 1 triangle
			glDisableVertexAttribArray(0);
			glDisableVertexAttribArray(1);

			glfwSwapBuffers(window.window);
			glfwPollEvents();
		}
		glDeleteBuffers(1, &vertexbuffer);
		glDeleteVertexArrays(1, &VertexArrayID);
		/*
		glDeleteShader(vertex_shader);
		glDeleteShader(fragment_shader);
		*/
		glDeleteProgram(programID);
	}

	void render()
	{

	}

	void init()
	{
		glewExperimental = true;
		if (!glfwInit()) {
			throw std::runtime_error("Failed to initialize GLFW");
		} 

		// Hints should apply to all windows
		glfwWindowHint(GLFW_SAMPLES, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
		//glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

		GLint flag;
		glGetIntegerv(GL_CONTEXT_FLAGS, &flag);
		if (flag & GL_CONTEXT_FLAG_DEBUG_BIT) {
			glEnable(GL_DEBUG_OUTPUT);
			glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
			glDebugMessageCallback(glDebugOutput, nullptr);
			glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
		}
	}	
};

int main()
{
	Main game;

	try {
		game.run();
	} catch (std::runtime_error& e) {
		std::cerr << e.what() << std::endl;	
	} catch (std::exception& e) {
		std::cerr << e.what() << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
