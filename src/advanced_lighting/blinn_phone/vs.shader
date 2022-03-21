#version 460 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormals;
layout(location = 2) in vec2 aTexcoords;


uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

out vec2 in_tex;
out vec3 fragment_normal;
out vec3 fragment_pos;

void main()
{
    gl_Position = projection * view * model * vec4(aPos, 1.0);
    fragment_normal = normalize(vec3(model * vec4(aNormals, 1.0)));
    fragment_pos = vec3(model * vec4(aPos, 1.0));
    in_tex = aTexcoords;
}