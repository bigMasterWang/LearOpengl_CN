#version 460 core
out vec4 FragColor;


in vec2 my_texture;
// 片段法向量
in vec3 my_fragment_normalize;
//片段位置
in vec3 my_fragment_pos;



void main()
{
    //光源颜色
    FragColor = vec4(1.0, 1.0, 1.0, 1.0);
}