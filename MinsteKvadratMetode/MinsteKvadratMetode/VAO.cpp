#include"VAO.h"

VAO::VAO()
{
	glGenVertexArrays(1, &ID); //Generate the VAO
}

void VAO::LinkVBO(VBO& VBO, GLuint layout)
{
	VBO.Bind(); //Bind the VBO
	glVertexAttribPointer(layout, 3, GL_FLOAT, GL_FALSE, 0, (void*)0); //Link the VBO to the VAO
	glEnableVertexAttribArray(layout); //Enable the VAO
	VBO.Unbind(); //Unbind the VBO
}

void VAO::Bind()
{
	glBindVertexArray(ID); //Bind the VAO
}

void VAO::Unbind()
{
	glBindVertexArray(0); //Unbind the VAO
}

void VAO::Delete()
{
	glDeleteVertexArrays(1, &ID); //Delete the VAO
}