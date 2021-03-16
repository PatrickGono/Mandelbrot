#include "Shader.h"

Shader::Shader(const char * vertexShaderPath, const char * fragmentShaderPath)
{
	program_ID = glCreateProgram();

	add_shader(program_ID, vertexShaderPath, GL_VERTEX_SHADER);
	add_shader(program_ID, fragmentShaderPath, GL_FRAGMENT_SHADER);

	glLinkProgram(program_ID);

	int success;
	char error_message[512];
	glGetProgramiv(program_ID, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(program_ID, 512, nullptr, error_message);
		std::cout << "Error linking shader program: " << error_message << "\n";
	}
}

Shader::~Shader()
{
	if (program_ID != 0)
	{
		glDeleteProgram(program_ID);
		program_ID = 0;
	}
}

void Shader::use_shader()
{
	glUseProgram(program_ID);
}


std::string Shader::read_shader_file(const char * filePath)
{
	std::string code;
	std::ifstream shader_file(filePath, std::ios::in);

	if (!shader_file)
	{
		std::cout << "Failed to open shader file: " << filePath << "\n";
		return "";
	}

	std::string line = "";
	while (std::getline(shader_file, line))
	{
		code.append(line + '\n');
	}
		
	shader_file.close();
	return code;
}

void Shader::add_shader(unsigned int program, const char * shaderPath, GLenum shaderType)
{
	std::string shader_string = read_shader_file(shaderPath);

	const GLchar * code[1];
	code[0] = shader_string.c_str();

	GLint code_length[1];
	code_length[0] = strlen(shader_string.c_str());

	unsigned int shader;
	int success;
	char error_message[512];

	shader = glCreateShader(shaderType);
	glShaderSource(shader, 1, code, code_length);
	glCompileShader(shader);

	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shader, 512, nullptr, error_message);
		std::cout << "Error compiling shader: " << error_message << "\n";
		std::cout << "Shader location: " << shaderPath << "\n";
	}

	glAttachShader(program, shader);
}


void Shader::set_bool(const std::string & name, bool value) const
{
	glUniform1i(glGetUniformLocation(program_ID, name.c_str()), (int)value);
}

void Shader::set_int(const std::string & name, int value) const
{
	glUniform1i(glGetUniformLocation(program_ID, name.c_str()), value);
}

void Shader::set_float(const std::string & name, float value) const
{
	glUniform1f(glGetUniformLocation(program_ID, name.c_str()), value);
}

void Shader::set_vec3(const std::string & name, float x, float y, float z) const
{
	glUniform3f(glGetUniformLocation(program_ID, name.c_str()), x, y, z);
}

void Shader::set_mat4(const std::string & name, glm::mat4 matrix) const
{
	glUniformMatrix4fv(glGetUniformLocation(program_ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(matrix));
}
