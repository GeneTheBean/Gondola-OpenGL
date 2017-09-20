//Eugene Chen Lol i forgot it was due on tuesday


// Local Headers
#include "glitter.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp> // after <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "glm/ext.hpp"          // to print vectors and matrices

// System Headers
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "SceneNode.h";
#include "Gondola.h";

// Standard Headers
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <vector>
// callback for keyboard input
void character_callback(GLFWwindow* window, unsigned int codepoint)
{
	if (codepoint == 'q') glfwSetWindowShouldClose(window, true);	//closes window
}



const GLchar* vertexSource =
"#version 150 core\n"             // glsl version
"in vec2 position;"               // expects 2 values for position
"in vec3 color;"                  // and 3 values for color
"out vec3 Color;"                 // will pass color along pipeline
"uniform mat4 model;"             // uniform = the same for all vertices
"void main()"
"{"
"    Color = color;"								    // just pass color along without modifying it
"    gl_Position = model * vec4(position, 0.0, 1.0);"   // gl_Position is special variable for final position
"}";                                                    // must be in homogeneous coordinates -- put in 0 for z and 1 for w
														// multiply by model matrix to transform
const GLchar* fragmentSource =
"#version 150 core\n"
"in vec3 Color;"
"out vec4 outColor;"
"void main()"
"{"
"    outColor = vec4(Color, 1.0);"
"}";

int main(int argc, char * argv[]) {
	// Load GLFW and Create a Window
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
	auto mWindow = glfwCreateWindow(mWidth, mHeight, "CISC3620", nullptr, nullptr);
	// Check for Valid Context
	if (mWindow == nullptr) {
		fprintf(stderr, "Failed to Create OpenGL Context");
		return EXIT_FAILURE;
	}
	glfwSetCharCallback(mWindow, character_callback);
	
	// Create Context and Load OpenGL Functions
	glfwMakeContextCurrent(mWindow);
	gladLoadGL();
	fprintf(stderr, "OpenGL %s\n", glGetString(GL_VERSION));
	
	// Create and compile the vertex shader
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	glCompileShader(vertexShader);

	// Create and compile the fragment shader
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	glCompileShader(fragmentShader);

	// Link the vertex and fragment shader into a shader program
	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glBindFragDataLocation(shaderProgram, 0, "outColor");
	glLinkProgram(shaderProgram);
	glUseProgram(shaderProgram);

	Gondola gondola (shaderProgram);
	
	// Rendering Loop
	while (glfwWindowShouldClose(mWindow) == false) {
		// Clear the screen to black
		glClearColor(0.0f, 0.0f, 0.5f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//Display gondola
		gondola.display();

		// Flip Buffers and Draw
		glfwSwapBuffers(mWindow);
		glfwPollEvents();
	}   glfwTerminate();

	// clean up
	glDeleteProgram(shaderProgram);
	glDeleteShader(fragmentShader);
	glDeleteShader(vertexShader);

	return EXIT_SUCCESS;
}

