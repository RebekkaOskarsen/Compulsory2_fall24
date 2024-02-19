#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<stb/stb_image.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<vector>


#include "Camera.h"
using namespace std;

const unsigned int width = 800;
const unsigned int height = 800;

//Points to calculate the minste kvadrat metoden
vector<glm::vec2> points =
{
    {2.0f, 0.0f},
    {3.0f, 3.0f},
    {4.0f, 1.0f},
    {5.0f, 2.0f},
    {5.0f, 4.0f},
    {6.0f, 3.0f},
    {6.0f, 6.0f}
};

glm::vec3 estimateParabolaParameters(const std::vector<glm::vec2>& points)
{
    int n = points.size();
    float sumX = 0, sumY = 0, sumX2 = 0, sumX3 = 0, sumX4 = 0, sumXY = 0, sumX2Y = 0;

    for (const auto& point : points)
    {
        float x = point.x;
        float y = point.y;
        sumX += x;
        sumY += y;
        sumX2 += x * x;
        sumX3 += x * x * x;
        sumX4 += x * x * x * x;
        sumXY += x * y;
        sumX2Y += x * x * y;
    }

    glm::mat3 A = glm::mat3(n, sumX, sumX2, sumX, sumX2, sumX3, sumX2, sumX3, sumX4);
    glm::vec3 B = glm::vec3(sumY, sumXY, sumX2Y);
    glm::vec3 result = glm::inverse(A) * B;

    return result;
}

void renderParabola(const glm::vec3& coefficients)
{
    glPointSize(5.0f);
    glColor3f(1.0f, 0.0f, 0.0f);

    glBegin(GL_POINTS);
    for (float x = 2.0f; x <= 6.0f; x += 0.01f) {
        float y = coefficients.x * x * x + coefficients.y * x + coefficients.z;
        glVertex2f(x, y);
    }
    glEnd();
}

void renderPoints()
{
    glBindVertexArray(VAO);
    glDrawArrays(GL_POINTS, 7, 7); // Draw points starting from index 7
    glBindVertexArray(0);
}

int main()
{
    //Initialize GLFW
    glfwInit();

    //Tell GLFW what version of OpenGL we are using, using version 3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);



    //Create a window
    GLFWwindow* window = glfwCreateWindow(width, height, "OpenGL", NULL, NULL); //With, hight, name, fullscreen or not, not important
    if (window == NULL)
    {
        cout << "Failed to create GLFW window" << endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window); //Make the window the current context

    //Initialize GLAD
    gladLoadGL();

    //Set the viewport
    glViewport(0, 0, width, height);



    //Main loop
    while (!glfwWindowShouldClose(window))
    {
        //Render
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f); //Set the window color 
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Clear the window and the depth buffer

        renderPoints();

        renderParabola(coefficients);

        glfwSwapBuffers(window);

        //This is the event handling part and takes care of all GLFW events 
        // It is important to keep it in the loop
        glfwPollEvents();

    }


    glfwTerminate();

    return 0;
}