#ifndef SHADER_CLASS_H
#define SHADER_CLASS_H
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cerrno>

using namespace std;

string get_file_contents(const char* filename); //Function to read the shader files

//Shader class
class Shader
{
public:
	GLuint ID;
	Shader(const char* vertexFile, const char* fragmentFile);

    // Method to set a vec3 uniform in the shader program
    void SetVec3(const std::string& name, const glm::vec3& value) const {
        GLint location = glGetUniformLocation(ID, name.c_str());
        if (location != -1) {
            glUniform3fv(location, 1, glm::value_ptr(value));
        }
        else {
            std::cerr << "Uniform " << name << " not found in shader program" << std::endl;
        }
    }

    // Method to set a vec2 uniform in the shader program
    void SetVec2(const std::string& name, const glm::vec2& value) const {
        GLint location = glGetUniformLocation(ID, name.c_str());
        if (location != -1) {
            glUniform2fv(location, 1, glm::value_ptr(value));
        }
        else {
            std::cerr << "Uniform " << name << " not found in shader program" << std::endl;
        }
    }

	void Activate();
	void Delete();
};

#endif

