#version 460 core



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
// 观察角度
uniform vec3 view_pos;


struct Material
{
	sampler2D diffuse_color;		// 漫反射的颜色
	sampler2D mirror_color;			// 镜面反射的颜色
	float shininess;				// 镜面反射的系数
};
uniform Material material;

struct Light
{
	vec3 diffuse_color;				// 漫反射的颜色
	vec3 environment_color;			// 镜面反射的颜色
	vec3 mirror_color;				// 镜面反射的颜色
};
uniform Light light;


// 物体的漫反射贴图, 直接应用到了环境光里面
// 将物体的镜面反射颜色换成贴图
void main()
{
	// fragment_color = texture(material.diffuse_color, my_texture);

	// 计算漫反射
	vec3 light_dir = normalize(light_pos - my_fragment_pos);
	float diffuse = max(dot(light_dir, my_fragment_normalize), 0.0);
	vec3 diffuse_light = diffuse * light.diffuse_color * vec3(texture(material.diffuse_color, my_texture));

	// 环境光
	vec3 environment_light = light.environment_color * vec3(texture(material.diffuse_color, my_texture));

	//镜面反射光
	vec3 view_dir = normalize(view_pos - my_fragment_pos);
	vec3 mirror_dir = reflect(-light_dir, my_fragment_normalize);
	// 为什么这个地方能决定散射??????
	float mirror = pow(max(dot(mirror_dir, view_dir), 0.0), material.shininess);
	// 木材没有镜面高光
	vec3 mirror_light = mirror * light.mirror_color * vec3(texture(material.mirror_color, my_texture));



	// vec3 real_color = objectColor * (diffuse_light + environment_light + mirror_light);
	vec3 real_color = diffuse_light + environment_light + mirror_light;
	fragment_color = vec4(real_color, 1.0);
};




