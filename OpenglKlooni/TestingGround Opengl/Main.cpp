#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>


#include "shaderClass.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"




int main()
{

	int height = 800;
	int width = 600;

	GLfloat vertices[] =
	{
	   -0.5, -0.5 * float(sqrt(3)) / 3, 0.0f,
	   0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,
	   0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f,
	   -0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f,
	   0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f,
	   0.0f, -0.5f * float(sqrt(3)) / 3, 0.0f

	};

	GLuint indices[] =
	{
		0, 3, 5, // Ala vasen kulma
		3, 2, 4, // Ala oikea kulma
		5, 4, 1 //Yl? Kolmio
	};


	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(height, width, "IMPORT OBJECTS", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	gladLoadGL();
	glViewport(0, 0, height, width);


	Shader shaderProgram("default.vert", "default.frag");

	VAO VAO1;
	VAO1.Bind();

	VBO VBO1(vertices, sizeof(vertices));
	EBO EBO1(indices, sizeof(indices));
	
	VAO1.LinkVBO(VBO1, 0);
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();


	while (!glfwWindowShouldClose(window)) {
		glClearColor(0.07f, 0.14f, 0.17f, 1.0f);
		// Clean the back buffer and assign the new color to it
		glClear(GL_COLOR_BUFFER_BIT);
		shaderProgram.Activate();
		VAO1.Bind();
		
		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
		
		
		// Swap the back buffer with the front buffer
		glfwSwapBuffers(window);
		glfwPollEvents();

	}
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	glfwDestroyWindow(window);
	glfwTerminate();


	return 0;
}