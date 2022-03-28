#version 460 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aTexcoords;
layout(location = 3) in vec3 aTangent;
layout(location = 4) in vec3 aBitangent;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

uniform vec3 lightPos;
uniform vec3 viewPos;

out VS_OUT{
    vec3 FragPos;
    vec2 TexCoords;
    vec3 TangentLightPos;
    vec3 TangentViewPos;
    vec3 TangentFragPos;
} vs_out;



uniform int use_phone;
void main()
{
    gl_Position = projection * view * model * vec4(aPos, 1.0);
    vs_out.FragPos = vec3(model * vec4(aPos, 1.0));
    vs_out.TexCoords = aTexcoords;

    // 法线的变化就是逆矩阵的转置
    mat3 normalMatrix = transpose(inverse(mat3(model)));


    vec3 T = normalize(normalMatrix * aTangent);
    vec3 N = normalize(normalMatrix * aNormal);
    //T = normalize(T - dot(T, N) * N);
    vec3 B = cross(N, T);
    //vec3 B = aBitangent;
    mat3 TBN = transpose(mat3(T, B, N));

    if (use_phone == 1)
    {
        vs_out.TangentLightPos = TBN * lightPos;
        vs_out.TangentViewPos = TBN * viewPos;
        vs_out.TangentFragPos = TBN * vs_out.FragPos;
    }
    else
    {
        vs_out.TangentLightPos = lightPos;
        vs_out.TangentViewPos = viewPos;
        vs_out.TangentFragPos = vs_out.FragPos;
    }
}