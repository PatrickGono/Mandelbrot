#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GLM/glm.hpp>
#include <GLM/gtc/type_ptr.hpp>

class Shader
{
public:
	unsigned int program_ID;
	Shader(const char * vertexShaderPath, const char * fragmentShaderPath);
	~Shader();

	void use_shader();

	void set_bool(const std::string & name, bool value) const;
	void set_int(const std::string & name, int value) const;
	void set_float(const std::string & name, float value) const;
	void set_vec3(const std::string & name, float x, float y, float z) const;
	void set_mat4(const std::string & name, glm::mat4 matrix) const;

private:
	std::string read_shader_file(const char * filePath);
	void add_shader(unsigned int program, const char * shaderPath, GLenum shaderType);
};

