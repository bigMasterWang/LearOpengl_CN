#version 460 core
out vec4 FragColor;

uniform vec3 lightColor;

void main()
{
    //��Դ��ɫ
    FragColor = vec4(lightColor.xyz, 1.0);
}