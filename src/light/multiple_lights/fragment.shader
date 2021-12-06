#version 460 core

out vec4 fragment_color;
in vec2 my_texture;
//片段法向量
in vec3 my_fragment_normalize;
//片段位置
in vec3 my_fragment_pos;
// 观察角度
uniform vec3 view_pos;



struct Material
{
	sampler2D diffuse_color;		// 漫反射的颜色
	sampler2D mirror_color;			// 镜面反射的颜色
	float shininess;				// 镜面反射的系数

	sampler2D special_color;		// 一个应用在手电筒上的照片
};
uniform Material material;


// 环境光
struct DirLight
{
	vec3 direction;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};
uniform DirLight dir_light;

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
	// 计算漫反射
	vec3 light_dir = -normalize(light.direction);
	float diffuse = max(dot(light_dir, normal), 0.0);
	vec3 diffuse_light = diffuse * light.diffuse * vec3(texture(material.diffuse_color, my_texture));

	// 环境光(漫反射, 当成环境光吧)
	vec3 environment_light = light.ambient * vec3(texture(material.diffuse_color, my_texture));

	//镜面反射光
	vec3 mirror_dir = reflect(light_dir, my_fragment_normalize);
	// 为什么这个地方能决定散射??????
	float mirror = pow(max(dot(mirror_dir, viewDir), 0.0), material.shininess);
	// 木材没有镜面高光
	vec3 mirror_light = mirror * light.specular * vec3(texture(material.mirror_color, my_texture));

	return diffuse_light + environment_light + mirror_light;
}


struct PointLight
{
	vec3 position;					// 点光源位置
	vec3 diffuse;					// 漫反射的颜色
	vec3 ambient;					// 环境光
	vec3 specular;					// 镜面反射的颜色

	float constant;
	float linear;
	float quadratic;
};
#define NR_POINT_LIGHTS  4
uniform PointLight point_light[NR_POINT_LIGHTS];


vec3 CalcPointLight(PointLight light, vec3 normal, vec3 viewDir)
{
	// 计算出常量
	float distance = length(light.position - my_fragment_pos);
	float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));


	vec3 light_dir = normalize(light.position - my_fragment_pos);
	// 计算漫反射
	float diffuse = max(dot(light_dir, my_fragment_normalize), 0.0);
	vec3 diffuse_light = diffuse * light.diffuse * vec3(texture(material.diffuse_color, my_texture));
	diffuse_light *= attenuation;

	// 环境光
	vec3 environment_light = light.ambient * vec3(texture(material.diffuse_color, my_texture));
	environment_light *= attenuation;

	//镜面反射光
	vec3 mirror_dir = reflect(-light_dir, my_fragment_normalize);
	// 为什么这个地方能决定散射??????
	float mirror = pow(max(dot(mirror_dir, -viewDir), 0.0), material.shininess);
	// 木材没有镜面高光
	vec3 mirror_light = mirror * light.specular * vec3(texture(material.mirror_color, my_texture));
	mirror_light *= attenuation;

	return diffuse_light + environment_light + mirror_light;
}



struct FlashLight
{
	vec3  position;     // 照相机位置
	vec3  direction;    // 照相机方向
	float cutOff;       // 给光源加上切光角的cos值
	float outCutOff;	// 外圆锥余弦值
};
uniform FlashLight flash_light;


vec3 CalcFlashLight(FlashLight light)
{
	//不要环境光了

	float theta = dot(normalize(flash_light.direction), normalize(my_fragment_pos - flash_light.position));
	float epsilon = flash_light.cutOff - flash_light.outCutOff;
	float intensity = clamp((theta - flash_light.outCutOff) / epsilon, 0.0, 1.0);

	// vec3 flush_color = vec3(texture(material.diffuse_color, my_texture));
	vec3 flush_color = vec3(texture(material.special_color, my_texture));
	return flush_color * intensity;
}




// 物体的漫反射贴图, 直接应用到了环境光里面
// 将物体的镜面反射颜色换成贴图
void main()
{
	vec3 view_dir = normalize(my_fragment_pos - view_pos);
	vec3 dir_color = CalcDirLight(dir_light, my_fragment_normalize, view_dir);
	vec3 point_color_0 = CalcPointLight(point_light[0], my_fragment_normalize, view_dir);
	vec3 point_color_1 = CalcPointLight(point_light[1], my_fragment_normalize, view_dir);
	vec3 point_color_2 = CalcPointLight(point_light[2], my_fragment_normalize, view_dir);
	vec3 point_color_3 = CalcPointLight(point_light[3], my_fragment_normalize, view_dir);
	vec3 flash_color = CalcFlashLight(flash_light);
	fragment_color = vec4(dir_color + point_color_0 + point_color_1 + point_color_2 + point_color_3 + flash_color, 1.0);
};




