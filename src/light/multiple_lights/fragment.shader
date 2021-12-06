#version 460 core

out vec4 fragment_color;
in vec2 my_texture;
//Ƭ�η�����
in vec3 my_fragment_normalize;
//Ƭ��λ��
in vec3 my_fragment_pos;
// �۲�Ƕ�
uniform vec3 view_pos;



struct Material
{
	sampler2D diffuse_color;		// ���������ɫ
	sampler2D mirror_color;			// ���淴�����ɫ
	float shininess;				// ���淴���ϵ��

	sampler2D special_color;		// һ��Ӧ�����ֵ�Ͳ�ϵ���Ƭ
};
uniform Material material;


// ������
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
	// ����������
	vec3 light_dir = -normalize(light.direction);
	float diffuse = max(dot(light_dir, normal), 0.0);
	vec3 diffuse_light = diffuse * light.diffuse * vec3(texture(material.diffuse_color, my_texture));

	// ������(������, ���ɻ������)
	vec3 environment_light = light.ambient * vec3(texture(material.diffuse_color, my_texture));

	//���淴���
	vec3 mirror_dir = reflect(light_dir, my_fragment_normalize);
	// Ϊʲô����ط��ܾ���ɢ��??????
	float mirror = pow(max(dot(mirror_dir, viewDir), 0.0), material.shininess);
	// ľ��û�о���߹�
	vec3 mirror_light = mirror * light.specular * vec3(texture(material.mirror_color, my_texture));

	return diffuse_light + environment_light + mirror_light;
}


struct PointLight
{
	vec3 position;					// ���Դλ��
	vec3 diffuse;					// ���������ɫ
	vec3 ambient;					// ������
	vec3 specular;					// ���淴�����ɫ

	float constant;
	float linear;
	float quadratic;
};
#define NR_POINT_LIGHTS  4
uniform PointLight point_light[NR_POINT_LIGHTS];


vec3 CalcPointLight(PointLight light, vec3 normal, vec3 viewDir)
{
	// ���������
	float distance = length(light.position - my_fragment_pos);
	float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));


	vec3 light_dir = normalize(light.position - my_fragment_pos);
	// ����������
	float diffuse = max(dot(light_dir, my_fragment_normalize), 0.0);
	vec3 diffuse_light = diffuse * light.diffuse * vec3(texture(material.diffuse_color, my_texture));
	diffuse_light *= attenuation;

	// ������
	vec3 environment_light = light.ambient * vec3(texture(material.diffuse_color, my_texture));
	environment_light *= attenuation;

	//���淴���
	vec3 mirror_dir = reflect(-light_dir, my_fragment_normalize);
	// Ϊʲô����ط��ܾ���ɢ��??????
	float mirror = pow(max(dot(mirror_dir, -viewDir), 0.0), material.shininess);
	// ľ��û�о���߹�
	vec3 mirror_light = mirror * light.specular * vec3(texture(material.mirror_color, my_texture));
	mirror_light *= attenuation;

	return diffuse_light + environment_light + mirror_light;
}



struct FlashLight
{
	vec3  position;     // �����λ��
	vec3  direction;    // ���������
	float cutOff;       // ����Դ�����й�ǵ�cosֵ
	float outCutOff;	// ��Բ׶����ֵ
};
uniform FlashLight flash_light;


vec3 CalcFlashLight(FlashLight light)
{
	//��Ҫ��������

	float theta = dot(normalize(flash_light.direction), normalize(my_fragment_pos - flash_light.position));
	float epsilon = flash_light.cutOff - flash_light.outCutOff;
	float intensity = clamp((theta - flash_light.outCutOff) / epsilon, 0.0, 1.0);

	// vec3 flush_color = vec3(texture(material.diffuse_color, my_texture));
	vec3 flush_color = vec3(texture(material.special_color, my_texture));
	return flush_color * intensity;
}




// �������������ͼ, ֱ��Ӧ�õ��˻���������
// ������ľ��淴����ɫ������ͼ
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




