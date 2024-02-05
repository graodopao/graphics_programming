// This file was written following the tutorial at learnopengl.com

#include <iostream>
#include "shader.hpp"
#include <GLFW/glfw3.h>


// Callbacks
void framebuffer_size_callback(GLFWwindow*, int width, int height)
{
	glViewport(0, 0, width, height);
}

// Misc
void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

int main() {
	
	// glfw initialization
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Window creation
	GLFWwindow* window{ glfwCreateWindow(1280, 720, "Nashira", NULL, NULL) };
	if (window == NULL) 
	{
		std::cout << "Failed to create GLFW window";
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	// glad initilization
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) 
	{
		std::cout << "Failed to initialize GLAD";
		return -1;
	}
	glViewport(0, 0, 1280, 720);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// Makes it so my GPU isn't at 100% at all times :)
	glfwSwapInterval(1);

	Shader defaultShader{"shader.vertex", "shader.frag"};


	
	// Triangle mesh
	float vertices[]{
		// points          // colors
		 0.0f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f,  // top right
		 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, // bottom right
		-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f  // top left 
	};

	unsigned int VBO, VAO;

	// VBO
	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// VAO
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	
	
	// loop
	while (!glfwWindowShouldClose(window)) 
	{
		// Setting the uniform
		float offset = 0.0f;
		defaultShader.setFloat("horizontalOffset", offset);


		processInput(window);

		// rendering commants here
		glClearColor(40.0f / 255.0f, 28.0f / 255.0f, 51.0f / 255.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		defaultShader.use();

		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// Terminate
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glfwTerminate();

	return 0;
}


