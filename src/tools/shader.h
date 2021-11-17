#pragma once

class Shader
{
private:
	unsigned int shader_program;

public:
	~Shader();
	Shader(const char* vertex_shader_path, const char* fragment_shader_path);
	void bind();
	void unbind();
	void set_float(const char* name, float offset);
};
