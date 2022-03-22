#include"shader.h"
#include<glad/glad.h>
#include<fstream>
#include<sstream>
#include<iostream>
#include<string>
#include <gtc/type_ptr.hpp>



Shader::~Shader()
{
}


Shader::Shader(const char* vertex_shader_path, const char* fragment_shader_path, const char* geometry_shader_path)
{
	std::ifstream vs_reader;
	std::ifstream fs_reader;
	std::ifstream gm_reader;

	std::stringstream vs_ss, fs_ss, gm_ss;
	vs_reader.open(vertex_shader_path);
	fs_reader.open(fragment_shader_path);
	gm_reader.open(geometry_shader_path);

	vs_ss << vs_reader.rdbuf();
	fs_ss << fs_reader.rdbuf();
	gm_ss << gm_reader.rdbuf();

	vs_reader.close();
	fs_reader.close();
	gm_reader.close();

	std::string v = vs_ss.str();
	const char* vs_source_code = v.c_str();
	std::string f = fs_ss.str();
	const char* fs_source_code = f.c_str();
	std::string g = gm_ss.str();
	const char* gm_source_code = g.c_str();


	unsigned int vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex_shader, 1, &vs_source_code, nullptr);
	glCompileShader(vertex_shader);
	int  success;
	char infoLog[512];
	glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertex_shader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}


	unsigned int fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment_shader, 1, &fs_source_code, nullptr);
	glCompileShader(fragment_shader);
	glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragment_shader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::GRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	unsigned int geometry_shader = glCreateShader(GL_GEOMETRY_SHADER);
	glShaderSource(geometry_shader, 1, &gm_source_code, nullptr);
	glCompileShader(geometry_shader);
	glGetShaderiv(geometry_shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(geometry_shader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::GRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	//着色器程序
	shader_program = glCreateProgram();
	glAttachShader(shader_program, vertex_shader);
	glAttachShader(shader_program, fragment_shader);
	glAttachShader(shader_program, geometry_shader);
	glLinkProgram(shader_program);

	//(GLuint program, GLenum pname, GLint* params)
	glGetProgramiv(shader_program, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(shader_program, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}

	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);
	glDeleteShader(geometry_shader);
}


Shader::Shader(const char* vertex_shader_path, const char* fragment_shader_path)
{
	std::ifstream vs_reader;
	std::ifstream fs_reader;

	std::stringstream vs_ss, fs_ss;
	vs_reader.open(vertex_shader_path);
	fs_reader.open(fragment_shader_path);

	vs_ss << vs_reader.rdbuf();
	fs_ss << fs_reader.rdbuf();

	vs_reader.close();
	fs_reader.close();

	std::string v = vs_ss.str();
	const char* vs_source_code = v.c_str();
	std::string f = fs_ss.str();
	const char* fs_source_code = f.c_str();


	unsigned int vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex_shader, 1, &vs_source_code, nullptr);
	glCompileShader(vertex_shader);
	int  success;
	char infoLog[512];
	glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertex_shader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}


	unsigned int fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment_shader, 1, &fs_source_code, nullptr);
	glCompileShader(fragment_shader);
	glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertex_shader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::GRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	//着色器程序
	shader_program = glCreateProgram();
	glAttachShader(shader_program, vertex_shader);
	glAttachShader(shader_program, fragment_shader);
	glLinkProgram(shader_program);

	//(GLuint program, GLenum pname, GLint* params)
	glGetProgramiv(shader_program, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(shader_program, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}

	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);
}

void Shader::bind()
{
	glUseProgram(shader_program);
}


void Shader::unbind()
{
	glUseProgram(0);
}

void Shader::set_float(const char* name, float offset)
{
	int location = glGetUniformLocation(shader_program, name);
	glUniform1f(location, offset);
}

void Shader::set_int(const char* name, int _index)
{
	int location = glGetUniformLocation(shader_program, name);
	glUniform1i(location, _index);
}

void Shader::set_mat4(const char* name, glm::mat4* matrix)
{
	int location = glGetUniformLocation(shader_program, name);
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(*matrix));
}

void Shader::set_vec3(const char* name, glm::vec3* vector)
{
	int location = glGetUniformLocation(shader_program, name);
	bind();
	glUniform3fv(location, 1, glm::value_ptr(*vector));
}
