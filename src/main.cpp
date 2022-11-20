// #include <glad/glad.h>
// #include <GLFW/glfw3.h>
#include "../include/glad/glad.h"
#include "../include/GLFW/glfw3.h"
#include <iostream>
#include <math.h>


// Vertex shader source code
// const char* vertexShaderSource = "#version 330 core \n"
// "layout (location=0) in vec3 aPos;\n"
// "void main()\n"
// "{\n"
// "	gl_Position= vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
// "}\0";

// // fragment shader source code 
// const char * fragmentShaderSource = "#version 330 core\n"
// "out vec4 FragColor;\n"
// "void main()\n"
// "{\n"
// "	FragColor = vec4(0.8f, 0.3f, 0.02f, 1.0f);\n"
// "}\n\0";

const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";
//Fragment Shader source code
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(0.8f, 0.3f, 0.02f, 1.0f);\n"
"}\n\0";

using namespace std;
int main(int argc, char* argv[])
{
	// Initialize glfw
	glfwInit();

	// Tell GLFW what verison of the OpenGL we are using
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);

	// Tell GLFW we are using CORE profile, which means we only have 
	// the modern functions
	glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);

	//Vertices coordinates
	GLfloat vertices[]=
	{
		-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, //Lower left
		0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // lower right corner
		0.0f, 0.5f*float(sqrt(3)) * 2 / 3, 0.0f// Upper corner
	};


	// Create a window object 800 by 800 pixels and give it a name "myopengl"
	GLFWwindow* window = glfwCreateWindow(800,800,"MyOpenGL",NULL,NULL);
	if(window == NULL)
	{
		cout<<"Failed to create GLFW window"<<endl;
		return -1;
	}

	// Introduce the window to the current context
	glfwMakeContextCurrent(window);

	// Load GLAD so it configures OpenGL
	gladLoadGL();

	// Specify the viewport of OpenGL in the Window
	// In this case the viewport goes from x=0, y=0, to x=800, y=800
	glViewport(0,0,800,800);

	// Create Vertex Shader Object and get reference
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	// Attach Vertex Shader source to the vertex shader object
	glShaderSource(vertexShader, 1, &vertexShaderSource,NULL);
	// Compile vertex shader into machine code
	glCompileShader(vertexShader);

	// Create Fragment Shader Object and get reference
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	// Attach Fragment shader source to the fragment shader Object
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	// Compile fragment shader into machine code
	glCompileShader(vertexShader);

	// Create Program Object and get its reference
	GLuint shaderProgram = glCreateProgram();


	// Attach the vertex and the fragment shaders to the Shader Program
	glAttachShader(shaderProgram,vertexShader);
	glAttachShader(shaderProgram,fragmentShader);

	// Wrap-up/ link all the shaders together into the shader program.
	glLinkProgram(shaderProgram);


	// Delete the now useless shader and fragment objects
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);


	// Create reference containers for the Vertex Array Object and the vertex buffer object
	GLuint VBO, VAO;

	// Generate the VAO and VBO with only 1 object each
	glGenVertexArrays(1,&VAO);
	glGenBuffers(1,&VBO);

	// Make the VAO the current vertex array object by binding it
	glBindVertexArray(VAO);

	// Bind the VBO specifying it's a GL_ARRAY_BUFFER
	glBindBuffer(GL_ARRAY_BUFFER,VBO);

	// Introduce the vertices into the VBO
	glBufferData(GL_ARRAY_BUFFER,sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Configure the Vertex Attribute so that OpenGL knows how to read the VBO
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	// Enable the vertex attribute so that OpenGL knows to use it
	glEnableVertexAttribArray(0);

	// Bind both VAO and VBO to zero so we don't modify the VAO and VBO
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	// Specify the color of the background
	// glClearColor(0.07f, 0.13f,0.17f, 1.0f);

	// Clean the back buffer and assign the new color to it
	// glClear(GL_COLOR_BUFFER_BIT);

	// perform the swap so it displays
	glfwSwapBuffers(window);

	// main event loop
	while(!glfwWindowShouldClose(window))
	{
		// manage all glfw events
		glClearColor(0.07f, 0.13f,0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// Tell OpenGL which shader program we want to use.
		glUseProgram(shaderProgram);
		// Bind the VAO so OpenGL knows to use it.
		glBindVertexArray(VAO);
		// Draw the triangle using the GL_TRIANGLES primitive
		glDrawArrays(GL_TRIANGLES,0,3);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}


	// Delete all the objects that were created
	glDeleteVertexArrays(1,&VAO);
	glDeleteBuffers(1,&VBO);
	glDeleteProgram(shaderProgram);

	// Remove the window
	glfwDestroyWindow(window);

	glfwTerminate();
	return 0;
}