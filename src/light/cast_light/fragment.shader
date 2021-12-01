#version 460 core


struct Material
{
	sampler2D diffuse_color;		// 漫反射的颜色
	sampler2D mirror_color;			// 镜面反射的颜色
	float shininess;				// 镜面反射的系数
};
uniform Material material;

struct Light
{
	vec3 position;					// 点光源位置
	vec3 direction;					// 点光源有方向
	vec3 diffuse_color;				// 漫反射的颜色
	vec3 environment_color;			// 镜面反射的颜色
	vec3 mirror_color;				// 镜面反射的颜色

	float constant;
	float linear;
	float quadratic;
};
uniform Light light;

struct FlashLight
{
	vec3  position;     // 照相机位置
	vec3  direction;    // 照相机方向
	float cutOff;       // 给光源加上切光角的cos值
	float outCutOff;	// 外圆锥余弦值
};
uniform FlashLight flash_light;


out vec4 fragment_color;
in vec2 my_texture;
// 片段法向量
in vec3 my_fragment_normalize;
//片段位置
in vec3 my_fragment_pos;
//物体颜色
uniform vec3 objectColor;
//环境光颜色
uniform vec3 lightColor;
// 观察角度
uniform vec3 view_pos;
// 1 为定向光, 2为点光源, 3为聚光
uniform int light_form;


// 物体的漫反射贴图, 直接应用到了环境光里面
// 将物体的镜面反射颜色换成贴图
void main()
{
	if (light_form == 1)
	{
		// 计算漫反射
		vec3 light_dir = -light.direction;
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

		vec3 real_color = diffuse_light + environment_light + mirror_light;
		fragment_color = vec4(real_color, 1.0);
	}
	if (light_form == 2)
	{
		// 计算出常量
		float distance = length(light.position - my_fragment_pos);
		float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));


		// 计算漫反射
		vec3 light_dir = normalize(light.position - my_fragment_pos);
		float diffuse = max(dot(light_dir, my_fragment_normalize), 0.0);
		vec3 diffuse_light = diffuse * light.diffuse_color * vec3(texture(material.diffuse_color, my_texture));
		diffuse_light *= attenuation;

		// 环境光
		vec3 environment_light = light.environment_color * vec3(texture(material.diffuse_color, my_texture));
		environment_light *= attenuation;

		//镜面反射光
		vec3 view_dir = normalize(view_pos - my_fragment_pos);
		vec3 mirror_dir = reflect(-light_dir, my_fragment_normalize);
		// 为什么这个地方能决定散射??????
		float mirror = pow(max(dot(mirror_dir, view_dir), 0.0), material.shininess);
		// 木材没有镜面高光
		vec3 mirror_light = mirror * light.mirror_color * vec3(texture(material.mirror_color, my_texture));
		mirror_light *= attenuation;

		vec3 real_color = diffuse_light + environment_light + mirror_light;
		fragment_color = vec4(real_color, 1.0);
	}
	if (light_form == 3)
	{

		// 环境光
		vec3 environment_light = light.environment_color * vec3(texture(material.diffuse_color, my_texture));

		float theta = dot(normalize(flash_light.direction), normalize(my_fragment_pos - flash_light.position));
		float epsilon = flash_light.cutOff - flash_light.outCutOff;
		float intensity = clamp((theta - flash_light.outCutOff) / epsilon, 0.0, 1.0);


		vec3 flush_color = vec3(texture(material.diffuse_color, my_texture));
		vec3 real_color = environment_light + flush_color * intensity;
		fragment_color = vec4(real_color, 1.0);
	}
};




