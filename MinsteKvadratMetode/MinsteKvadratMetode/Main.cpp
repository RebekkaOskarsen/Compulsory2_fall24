#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<vector>

#include "shaderClass.h"
#include "VBO.h"
#include "VAO.h"
#include "Camera.h"

using namespace std;

const unsigned int width = 800;
const unsigned int height = 800;

// The points to draw
vector<pair<int, int>> points = 
{ 
	{2,0}, 
	{3,3}, 
	{4,1}, 
	{5,2}, 
	{5,4}, 
	{6,3}, 
	{6,6} 
};

GLfloat vertices[14]; // Each point has two coordinates


void savePointsToFile(const char* filename) {
	ofstream file(filename);
	if (!file) {
		cout << "Failed to open the file for writing." << endl;
		return;
	}

	for (const auto& point : points) {
		file << point.first << " " << point.second << endl;
	}

	file.close();
}


int main()
{
	glfwInit(); //Initialize GLFW

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); //Use OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //Use the core profile



	GLFWwindow* window = glfwCreateWindow(width, height, "Minste Kvadrat Metode", NULL, NULL); //Create a window
	if (window == NULL) //If the window was not created
	{
		cout << "Failed to create GLFW window" << endl;
		glfwTerminate(); //Terminate GLFW
		return -1;
	}
	glfwMakeContextCurrent(window); //Make the window the current context

	gladLoadGL(); //Load GLAD

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) //Initialize GLAD
	{
		cout << "Failed to initialize GLAD" << endl;
		return -1;
	}

	glViewport(0, 0, width, height); //Set the viewport

	cout << "OpenGL version: " << glGetString(GL_VERSION) << endl;

	Shader shaderProgram("default.vert", "default.frag"); //Create a shader program



	VAO VAO1; //Create a VAO
	VAO1.Bind(); //Bind the VAO

	// Create the vertices array
	for (size_t i = 0; i < points.size(); ++i)  // Copy the points to the vertices array
	{
		vertices[i * 2] = static_cast<float>(points[i].first);  // x-coordinate
		vertices[i * 2 + 1] = static_cast<float>(points[i].second);  // y-coordinate
	}

	savePointsToFile("points.txt");

	VBO VBO1(vertices, sizeof(vertices)); //Create a VBO

	VAO1.LinkVBO(VBO1, 0); //Link the VBO to the VAO
	VAO1.Unbind(); //Unbind the VAO
	VBO1.Unbind(); //Unbind the VBO

	Camera camera(width, height, glm::vec3(0.0f, 0.0f, 10.0f)); //Create a camera

	while (!glfwWindowShouldClose(window))
	{
		
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f); //Set the clear color
		glClear(GL_COLOR_BUFFER_BIT); //Clear the color buffer
		shaderProgram.Activate(); //Activate the shader program
		
		camera.Inputs(window); //Input to the camera
		camera.Matrix(45.0f, 0.1f, 100.0f, shaderProgram, "camMatrix"); //Create the camera matrix


		glPointSize(10.0f); // Set the point size
		glDrawArrays(GL_POINTS, 0, points.size()); // Draw the points

		VAO1.Bind(); //Bind the VAO


		glfwSwapBuffers(window); //Swap the buffers
		glfwPollEvents(); //Poll for events
		
	}

	VAO1.Delete(); //Delete the VAO
	VBO1.Delete(); //Delete the VBO
	shaderProgram.Delete(); //Delete the shader program

	glfwDestroyWindow(window); //Destroy the window

	glfwTerminate(); //Terminate GLFW
	return 0;

}
