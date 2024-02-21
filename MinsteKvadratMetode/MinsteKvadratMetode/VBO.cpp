#include"VBO.h"

VBO::VBO(GLfloat* vertices, GLsizeiptr size)
{
	glGenBuffers(1, &ID); //Generate the VBO
	glBindBuffer(GL_ARRAY_BUFFER, ID); //Bind the VBO
	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW); //Copy the vertices to the VBO
}

void VBO::Bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, ID); //Bind the VBO
}

void VBO::Unbind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0); //Unbind the VBO
}

void VBO::Delete()
{
	glDeleteBuffers(1, &ID); //Delete the VBO
}