#version 460 core
out vec4 FragColor;

uniform vec3 lightColor;


in vec2 my_texture;
// Ƭ�η�����
in vec3 my_fragment_normalize;
//Ƭ��λ��
in vec3 my_fragment_pos;



void main()
{
    //��Դ��ɫ
    FragColor = vec4(lightColor.xyz, 1.0);
}