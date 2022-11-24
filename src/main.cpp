#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <Eigen/Dense>

#include <iostream>
#include <stdexcept>

#include "utils/logging.hpp"
#include "utils/debugging.hpp"
#include "input/keyboard.hpp"
#include "renderer/shader.hpp"

using namespace Eigen;

class Main 
{
public:
	void run() 
	{
		init_GLFW();
		init_GLEW();
		utils::init_logger();
		main_loop();
		clean();
	}
private:
	const std::string vs_path = "../../src/shaders/vs.vert";
	const std::string fs_path = "../../src/shaders/fs.frag";

	GLFWwindow* window;
	GLuint programID;

	void main_loop() 
	{
		glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

		glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

		GLuint VertexArrayID;
		glGenVertexArrays(1, &VertexArrayID);
		glBindVertexArray(VertexArrayID);

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


		// Components of the model matrix

		Matrix<float, 4, 4, RowMajor> scale {
			{0.5f, 0.0f, 0.0f, 0.0f},
			{0.0f, 0.5f, 0.0f, 0.0f},
			{0.0f, 0.0f, 0.5f, 0.0f},
			{0.0f, 0.0f, 0.0f, 1.0f}
		};

		Matrix<float, 4, 4, RowMajor> rotate {
			{1.0f, 0.0f, 0.0f, 0.0f},
			{0.0f, 1.0f, 0.0f, 0.0f},
			{0.0f, 0.0f, 1.0f, 0.0f},
			{0.0f, 0.0f, 0.0f, 1.0f}
		};

		Matrix<GLfloat, 4, 4, RowMajor> translate {
			{1.0f, 0.0f, 0.0f, 0.0f},
			{0.0f, 1.0f, 0.0f, 0.0f},
			{0.0f, 0.0f, 1.0f, 0.0f},
			{0.0f, 0.0f, 0.0f, 1.0f}
		};

		Matrix<GLfloat, 4, 4, RowMajor> model {
			{1.0f, 0.0f, 0.0f, 0.0f},
			{0.0f, 1.0f, 0.0f, 0.0f},
			{0.0f, 0.0f, 1.0f, 0.0f},
			{0.0f, 0.0f, 0.0f, 1.0f},
		};

		Matrix<GLfloat, 4, 4, RowMajor> view {
			{1.0f, 0.0f, 0.0f, -4.0f},
			{0.0f, 1.0f, 0.0f, -4.0f},
			{0.0f, 0.0f, 1.0f, -3.0f},
			{0.0f, 0.0f, 0.0f, 1.0f},
		};

		/*
		// Camera matrix
		Matrix<float, 4, 4, RowMajor> projection {
			{4.0f, 3.0f, 3.0f, 0.0f},
			{0.0f, 0.0f, 0.0f, 0.0f},
			{0.0f, 1.0f, 0.0f, 0.0f},
			{0.0f, 0.0f, 0.0f, 1.0f}
		};

		GLuint mvpID = glGetUniformLocation(programID, "MVP"); 

		Matrix<float, 36, 4, RowMajor> vbd {
			{-1.0f,-1.0f,-1.0f, 1.0f}, // triangle 1 : begin
			{-1.0f,-1.0f, 1.0f, 1.0f},
			{-1.0f, 1.0f, 1.0f, 1.0f}, // triangle 1 : end
			{1.0f, 1.0f,-1.0f, 1.0f}, // triangle 2 : begin
			{-1.0f,-1.0f,-1.0f, 1.0f},
			{-1.0f, 1.0f,-1.0f, 1.0f}, // triangle 2 : end
			{1.0f,-1.0f, 1.0f, 1.0f},
			{-1.0f,-1.0f,-1.0f, 1.0f},
			{1.0f,-1.0f,-1.0f, 1.0f},
			{1.0f, 1.0f,-1.0f, 1.0f},
			{1.0f,-1.0f,-1.0f, 1.0f},
			{-1.0f,-1.0f,-1.0f, 1.0f},
			{-1.0f,-1.0f,-1.0f, 1.0f},
			{-1.0f, 1.0f, 1.0f, 1.0f},
			{-1.0f, 1.0f,-1.0f, 1.0f},
			{1.0f,-1.0f, 1.0f, 1.0f},
			{-1.0f,-1.0f, 1.0f, 1.0f},
			{-1.0f,-1.0f,-1.0f, 1.0f},
			{-1.0f, 1.0f, 1.0f, 1.0f},
			{-1.0f,-1.0f, 1.0f, 1.0f},
			{1.0f,-1.0f, 1.0f, 1.0f},
			{1.0f, 1.0f, 1.0f, 1.0f},
			{1.0f,-1.0f,-1.0f, 1.0f},
			{1.0f, 1.0f,-1.0f, 1.0f},
			{1.0f,-1.0f,-1.0f, 1.0f},
			{1.0f, 1.0f, 1.0f, 1.0f},
			{1.0f,-1.0f, 1.0f, 1.0f},
			{1.0f, 1.0f, 1.0f, 1.0f},
			{1.0f, 1.0f,-1.0f, 1.0f},
			{-1.0f, 1.0f,-1.0f, 1.0f},
			{1.0f, 1.0f, 1.0f, 1.0f},
			{-1.0f, 1.0f,-1.0f, 1.0f},
			{-1.0f, 1.0f, 1.0f, 1.0f},
			{1.0f, 1.0f, 1.0f, 1.0f},
			{-1.0f, 1.0f, 1.0f, 1.0f},
			{1.0f,-1.0f, 1.0f, 1.0f}
		};

		Matrix<float, 36, 3, RowMajor> cbd {
			{0.583f,  0.771f,  0.014f},
			{0.609f,  0.115f,  0.436f},
			{0.327f,  0.483f,  0.844f},
			{0.822f,  0.569f,  0.201f},
			{0.435f,  0.602f,  0.223f},
			{0.310f,  0.747f,  0.185f},
			{0.597f,  0.770f,  0.761f},
			{0.559f,  0.436f,  0.730f},
			{0.359f,  0.583f,  0.152f},
			{0.483f,  0.596f,  0.789f},
			{0.559f,  0.861f,  0.639f},
			{0.195f,  0.548f,  0.859f},
			{0.014f,  0.184f,  0.576f},
			{0.771f,  0.328f,  0.970f},
			{0.406f,  0.615f,  0.116f},
			{0.676f,  0.977f,  0.133f},
			{0.971f,  0.572f,  0.833f},
			{0.140f,  0.616f,  0.489f},
			{0.997f,  0.513f,  0.064f},
			{0.945f,  0.719f,  0.592f},
			{0.543f,  0.021f,  0.978f},
			{0.279f,  0.317f,  0.505f},
			{0.167f,  0.620f,  0.077f},
			{0.347f,  0.857f,  0.137f},
			{0.055f,  0.953f,  0.042f},
			{0.714f,  0.505f,  0.345f},
			{0.783f,  0.290f,  0.734f},
			{0.722f,  0.645f,  0.174f},
			{0.302f,  0.455f,  0.848f},
			{0.225f,  0.587f,  0.040f},
			{0.517f,  0.713f,  0.338f},
			{0.053f,  0.959f,  0.120f},
			{0.393f,  0.621f,  0.362f},
			{0.673f,  0.211f,  0.457f},
			{0.820f,  0.883f,  0.371f},
			{0.982f,  0.099f,  0.879f}
		};

		*/
		Matrix<GLfloat, 3, 3, RowMajor> vbd {
			{-1.0f, -1.0f, 0.0f},
			{1.0f, -1.0f, 0.0f},
			{0.0f,  1.0f, 0.0f},
		};

		

		/*
		Matrix<GLfloat, 3, 3, RowMajor> cbd {
			{1.0, 0.0, 0.0},
			{0.0, 1.0, 0.0},
			{0.0, 0.0, 1.0}
		};
		*/

		GLuint vertexbuffer;
		glGenBuffers(1, &vertexbuffer);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * vbd.size(), vbd.data(), GL_STATIC_DRAW);

		std::cout << "Got here!" << std::endl;

		/*
		GLuint colorbuffer;
		glGenBuffers(1, &colorbuffer);
		glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * cbd.size(), cbd.data(), GL_STATIC_DRAW);
		*/
		
		
		while (!glfwWindowShouldClose(window)) {
			// Clear the screen
			glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			// Use our shader
			glUseProgram(programID);

			//glUniformMatrix4fv(, 1, GL_FALSE, scale.data());

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

			/*
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
			*/
		

			// Draw the triangle !
			glDrawArrays(GL_TRIANGLES, 0, 3); // 3 indices starting at 0 -> 1 triangle
			glDisableVertexAttribArray(0);
			//glDisableVertexAttribArray(1);
			glfwSwapBuffers(window);
			glfwPollEvents();
		}
		glDeleteBuffers(1, &vertexbuffer);
		glDeleteVertexArrays(1, &VertexArrayID);
		glDeleteShader(vertex_shader);
		glDeleteShader(fragment_shader);
		glDeleteProgram(programID);
	}

	void init_GLFW()
	{
		if (!glfwInit()) {
			throw std::runtime_error("Failed to initialize GLFW");
		} 
		glfwWindowHint(GLFW_SAMPLES, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);


		GLint flag;
		glGetIntegerv(GL_CONTEXT_FLAGS, &flag);
		if (flag & GL_CONTEXT_FLAG_DEBUG_BIT) {
			glEnable(GL_DEBUG_OUTPUT);
			glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
			glDebugMessageCallback(glDebugOutput, nullptr);
			glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
		}

		window = glfwCreateWindow(1024, 768, "Flappy Bird", nullptr, nullptr);

		if (window == nullptr) {
			throw std::runtime_error("Failed to create window.");
		}

		glfwSetKeyCallback(window, key_callback);
		glfwMakeContextCurrent(window);
	}	

	void init_GLEW()
	{
		glewExperimental = true;
		if (glewInit() != GLEW_OK) {
			throw std::runtime_error("Failed to initialize GLEW");
		} 
	}

	template<typename T>
	void print_2darray(T *arr, int m, int n)
	{
		for (int i = 0; i < m; i++) {
			for (int j = 0; j < n; j++) {
				std::cout << *(arr + (i * n) + j) << " ";
			}
			std::cout << std::endl;
		}

	}

	void clean()
	{
		glfwTerminate();
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
