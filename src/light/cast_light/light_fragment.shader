#version 460 core
out vec4 FragColor;


in vec2 my_texture;
// Ƭ�η�����
in vec3 my_fragment_normalize;
//Ƭ��λ��
in vec3 my_fragment_pos;



void main()
{
    //��Դ��ɫ
    FragColor = vec4(1.0, 1.0, 1.0, 1.0);
}