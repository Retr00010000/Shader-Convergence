#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

#include"shaderClass.h"
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"



// Vertex positions followed by RGB colors.
GLfloat vertices[] =
{
	// Position                    // RGB                         Vertex
	-0.75f,   -0.60f,    0.0f,     0.80f,  0.00f,  0.05f, // 0: red
	-0.375f,  -0.60f,    0.0f,     0.90f,  0.425f, 0.025f,// 1
	 0.00f,   -0.60f,    0.0f,     1.00f,  0.85f,  0.00f, // 2: red + green
	 0.375f,  -0.60f,    0.0f,     0.50f,  0.675f, 0.06f, // 3
	 0.75f,   -0.60f,    0.0f,     0.00f,  0.50f,  0.12f, // 4: green

	-0.5625f, -0.275f,  0.0f,     0.825f, 0.00f,  0.525f,// 5
	-0.1875f, -0.275f,  0.0f,     0.925f, 0.425f, 0.50f, // 6
	 0.1875f, -0.275f,  0.0f,     0.50f,  0.85f,  0.50f, // 7
	 0.5625f, -0.275f,  0.0f,     0.00f,  0.675f, 0.56f, // 8

	-0.375f,   0.05f,   0.0f,     0.85f,  0.00f,  1.00f, // 9: red + blue
	 0.00f,    0.05f,   0.0f,     0.425f, 0.425f, 1.00f, // 10
	 0.375f,   0.05f,   0.0f,     0.00f,  0.85f,  1.00f, // 11: green + blue

	-0.1875f,  0.375f,  0.0f,     0.45f,  0.075f, 0.95f, // 12
	 0.1875f,  0.375f,  0.0f,     0.025f, 0.50f,  0.95f, // 13

	 0.00f,    0.70f,   0.0f,     0.05f,  0.15f,  0.90f  // 14: blue
};

// Indices for vertices order
GLuint indices[] =
{
	// Left large section
	0, 1, 5,
	1, 2, 6,
	5, 6, 9,

	// Right large section
	2, 3, 7,
	3, 4, 8,
	7, 8, 11,

	// Top large section
	9, 10, 12,
	10, 11, 13,
	12, 13, 14,

};



int main()
{
	// Initialize GLFW
	glfwInit();

	// Tell GLFW what version of OpenGL we are using 
	// In this case we are using OpenGL 4.6
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	// Tell GLFW we are using the CORE profile
	// So that means we only have the modern functions
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create a GLFWwindow object of 800 by 800 pixels, naming it "Hello Triangle"
	GLFWwindow* window = glfwCreateWindow(800, 800, "Hello Triangle", NULL, NULL);
	// Error check if the window fails to create
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	// Introduce the window into the current context
	glfwMakeContextCurrent(window);

	//Load GLAD so it configures OpenGL
	gladLoadGL();
	// Specify the viewport of OpenGL in the Window
	// In this case the viewport goes from x = 0, y = 0, to x = 800, y = 800
	glViewport(0, 0, 800, 800);



	// One shader program interpolates the RGB color stored at every vertex.
	Shader shaderProgram("default.vert", "default.frag");



	// Generates Vertex Array Object and binds it
	VAO VAO1;
	VAO1.Bind();

	// Generates Vertex Buffer Object and links it to vertices
	VBO VBO1(vertices, sizeof(vertices));
	// Generates Element Buffer Object and links it to indices
	EBO EBO1(indices, sizeof(indices));

	// Links position and color data from each interleaved vertex to the VAO.
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 6 * sizeof(GLfloat), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 6 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
	// Unbind all to prevent accidentally modifying them
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();



	// Main while loop
	while (!glfwWindowShouldClose(window))
	{
		// Specify the color of the background
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		// Clean the back buffer and assign the new color to it
		glClear(GL_COLOR_BUFFER_BIT);
		// Use the one program that interpolates the per-vertex RGB colors.
		shaderProgram.Activate();
		VAO1.Bind();
		// Draw primitives, number of indices, datatype of indices, index of indices
		glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(indices[0]), GL_UNSIGNED_INT, (void*)0);
		// Swap the back buffer with the front buffer
		glfwSwapBuffers(window);
		// Take care of all GLFW events
		glfwPollEvents();
	}



	// Delete all the objects we've created
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	shaderProgram.Delete();
	// Delete window before ending the program
	glfwDestroyWindow(window);
	// Terminate GLFW before ending the program
	glfwTerminate();
	return 0;
}
