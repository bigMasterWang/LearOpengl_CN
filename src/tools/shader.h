#pragma once
#include <gtc/type_ptr.hpp>

class Shader
{
private:
	unsigned int shader_program;

public:
	~Shader();
	Shader(const char* vertex_shader_path, const char* fragment_shader_path);
	Shader(const char* vertex_shader_path, const char* fragment_shader_path, const char* geometry_shader_path);
	void bind();
	void unbind();
	void set_float(const char* name, float offset);
	void set_int(const char* name, int _index);
	void set_mat4(const char* name, glm::mat4* matrix);
	void set_vec3(const char* name, glm::vec3* vector);
	inline int get_id() { return shader_program; }
};
