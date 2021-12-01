#version 460 core


struct Material
{
	sampler2D diffuse_color;		// ���������ɫ
	sampler2D mirror_color;			// ���淴�����ɫ
	float shininess;				// ���淴���ϵ��
};
uniform Material material;

struct Light
{
	vec3 position;					// ���Դλ��
	vec3 direction;					// ���Դ�з���
	vec3 diffuse_color;				// ���������ɫ
	vec3 environment_color;			// ���淴�����ɫ
	vec3 mirror_color;				// ���淴�����ɫ

	float constant;
	float linear;
	float quadratic;
};
uniform Light light;

struct FlashLight
{
	vec3  position;     // �����λ��
	vec3  direction;    // ���������
	float cutOff;       // ����Դ�����й�ǵ�cosֵ
	float outCutOff;	// ��Բ׶����ֵ
};
uniform FlashLight flash_light;


out vec4 fragment_color;
in vec2 my_texture;
// Ƭ�η�����
in vec3 my_fragment_normalize;
//Ƭ��λ��
in vec3 my_fragment_pos;
//������ɫ
uniform vec3 objectColor;
//��������ɫ
uniform vec3 lightColor;
// �۲�Ƕ�
uniform vec3 view_pos;
// 1 Ϊ�����, 2Ϊ���Դ, 3Ϊ�۹�
uniform int light_form;


// �������������ͼ, ֱ��Ӧ�õ��˻���������
// ������ľ��淴����ɫ������ͼ
void main()
{
	if (light_form == 1)
	{
		// ����������
		vec3 light_dir = -light.direction;
		float diffuse = max(dot(light_dir, my_fragment_normalize), 0.0);
		vec3 diffuse_light = diffuse * light.diffuse_color * vec3(texture(material.diffuse_color, my_texture));

		// ������
		vec3 environment_light = light.environment_color * vec3(texture(material.diffuse_color, my_texture));

		//���淴���
		vec3 view_dir = normalize(view_pos - my_fragment_pos);
		vec3 mirror_dir = reflect(-light_dir, my_fragment_normalize);
		// Ϊʲô����ط��ܾ���ɢ��??????
		float mirror = pow(max(dot(mirror_dir, view_dir), 0.0), material.shininess);
		// ľ��û�о���߹�
		vec3 mirror_light = mirror * light.mirror_color * vec3(texture(material.mirror_color, my_texture));

		vec3 real_color = diffuse_light + environment_light + mirror_light;
		fragment_color = vec4(real_color, 1.0);
	}
	if (light_form == 2)
	{
		// ���������
		float distance = length(light.position - my_fragment_pos);
		float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));


		// ����������
		vec3 light_dir = normalize(light.position - my_fragment_pos);
		float diffuse = max(dot(light_dir, my_fragment_normalize), 0.0);
		vec3 diffuse_light = diffuse * light.diffuse_color * vec3(texture(material.diffuse_color, my_texture));
		diffuse_light *= attenuation;

		// ������
		vec3 environment_light = light.environment_color * vec3(texture(material.diffuse_color, my_texture));
		environment_light *= attenuation;

		//���淴���
		vec3 view_dir = normalize(view_pos - my_fragment_pos);
		vec3 mirror_dir = reflect(-light_dir, my_fragment_normalize);
		// Ϊʲô����ط��ܾ���ɢ��??????
		float mirror = pow(max(dot(mirror_dir, view_dir), 0.0), material.shininess);
		// ľ��û�о���߹�
		vec3 mirror_light = mirror * light.mirror_color * vec3(texture(material.mirror_color, my_texture));
		mirror_light *= attenuation;

		vec3 real_color = diffuse_light + environment_light + mirror_light;
		fragment_color = vec4(real_color, 1.0);
	}
	if (light_form == 3)
	{

		// ������
		vec3 environment_light = light.environment_color * vec3(texture(material.diffuse_color, my_texture));

		float theta = dot(normalize(flash_light.direction), normalize(my_fragment_pos - flash_light.position));
		float epsilon = flash_light.cutOff - flash_light.outCutOff;
		float intensity = clamp((theta - flash_light.outCutOff) / epsilon, 0.0, 1.0);


		vec3 flush_color = vec3(texture(material.diffuse_color, my_texture));
		vec3 real_color = environment_light + flush_color * intensity;
		fragment_color = vec4(real_color, 1.0);
	}
};




