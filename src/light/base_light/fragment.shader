#version 460 core

uniform sampler2D texture1;
uniform sampler2D texture2;


out vec4 fragment_color;

in vec2 my_texture;
// 片段法向量
in vec3 my_fragment_normalize;
//片段位置
in vec3 my_fragment_pos;


//光照位置
uniform vec3 light_pos;
//物体颜色
uniform vec3 objectColor;
//环境光颜色
uniform vec3 lightColor;
//环境光系数
uniform float environment_coefficient;
// 观察角度
uniform vec3 view_pos;
// 镜面反射系数
uniform float mirror_coefficient;

void main()
{
	// fragment_color = mix(texture(texture1, my_texture), texture(texture2, my_texture), 0.5);
	// fragment_color = vec4(lightColor * objectColor, 1.0) * mix(texture(texture1, my_texture), texture(texture2, my_texture), 0.5);

	// 计算漫反射
	vec3 light_dir = normalize(light_pos - my_fragment_pos);
	float diffuse = max(dot(light_dir, my_fragment_normalize), 0.0);
	vec3 diffuse_light = diffuse * lightColor;

	// 环境光
	vec3 environment_light = environment_coefficient * lightColor;

	//镜面反射光
	vec3 view_dir = normalize(view_pos - my_fragment_pos);
	vec3 mirror_dir = reflect(-light_dir, my_fragment_normalize);
	// 为什么这个地方能决定散射??????
	float mirror = pow(max(dot(mirror_dir, view_dir), 0.0), 32);
	vec3 mirror_light = mirror * lightColor * mirror_coefficient;

	vec3 real_color = objectColor * (diffuse_light + environment_light + mirror_light);
	// vec3 real_color = objectColor * (diffuse_light + environment_light);
	fragment_color = vec4(real_color, 1.0);
};




