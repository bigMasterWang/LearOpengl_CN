#version 460 core



out vec4 fragment_color;
in vec2 my_texture;
// Ƭ�η�����
in vec3 my_fragment_normalize;
//Ƭ��λ��
in vec3 my_fragment_pos;
//����λ��
uniform vec3 light_pos;
//������ɫ
uniform vec3 objectColor;
//��������ɫ
uniform vec3 lightColor;
// �۲�Ƕ�
uniform vec3 view_pos;


struct Material
{
	sampler2D diffuse_color;		// ���������ɫ
	sampler2D mirror_color;			// ���淴�����ɫ
	float shininess;				// ���淴���ϵ��
};
uniform Material material;

struct Light
{
	vec3 diffuse_color;				// ���������ɫ
	vec3 environment_color;			// ���淴�����ɫ
	vec3 mirror_color;				// ���淴�����ɫ
};
uniform Light light;


// �������������ͼ, ֱ��Ӧ�õ��˻���������
// ������ľ��淴����ɫ������ͼ
void main()
{
	// fragment_color = texture(material.diffuse_color, my_texture);

	// ����������
	vec3 light_dir = normalize(light_pos - my_fragment_pos);
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



	// vec3 real_color = objectColor * (diffuse_light + environment_light + mirror_light);
	vec3 real_color = diffuse_light + environment_light + mirror_light;
	fragment_color = vec4(real_color, 1.0);
};




