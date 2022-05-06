#version 460 core
out vec4 FragColor;

in vec2 TexCoords;
in vec3 WorldPos;


uniform vec3 cameraPos;

uniform sampler2D normal_map;			//����
uniform sampler2D albedo_map;			//������
uniform sampler2D metallic_map;			//������
uniform sampler2D roughness_map;		//�ֲڶ�
uniform sampler2D ao_map;				//�������ڱ�


uniform vec3 lightPosition[4];
uniform vec3 lightColors[4];
in vec3 Normal;

const float PI = 3.14159265359;


// ���ط��������ı�ֵ�����Ǿ��淴���������ı�ֵ
// F0�Ǵ�ֱ��������ʱ���ж��ٹ��߱����䣬Ҳ����Ϊ0������ǵķ���
// �������Ե��0.04ʱ����ȥ����ȷ��
vec3 fresnel(vec3 H, vec3 V, vec3 albedo, float metallic)
{
	float cosTheta = max(dot(H, V), 0.0);
	vec3 F0 = vec3(0.04);
	F0 = mix(F0, albedo, metallic);
	return F0 + (1.0 - F0) * pow(clamp(1.0 - cosTheta, 0.0, 1.0), 5.0);
}



// ���߷ֲ�����,��ͳ��ѧ�Ͻ��Ƶı�ʾ����h����ȡ��һ�µ�΢ƽ��ı���
// ndf(n,h,a)
float normal_distributon(vec3 N, vec3 H, float roughness)
{
	float a = roughness;
	float a2 = a * a;
	float n_dot_h = max(dot(N, H), 0.0);
	float n_dot_h2 = n_dot_h * n_dot_h;
	float denom = PI * pow(n_dot_h2 * (a2 - 1) + 1, 2);
	return a2 / denom;
}


float geometry_schlick_ggx(float n_dot, float k)
{
	float nom = n_dot;
	float denom = n_dot * (1 - k) + k;
	return nom / denom;
}


// ���κ�������ͳ��ѧ�������΢ƽ����໥�ڱεı��ʣ�����Ĺ�������
// g(n,v,l,a)
float geometry(vec3 N, vec3 V, vec3 L, float roughness)
{
	float k_direct = pow(roughness + 1, 2) / 8.0;
	float n_dot_v = max(dot(N, V), 0.0);
	float n_dot_l = max(dot(N, L), 0.0);
	float ggx1 = geometry_schlick_ggx(n_dot_v, k_direct);
	float ggx2 = geometry_schlick_ggx(n_dot_l, k_direct);
	return ggx1 * ggx2;
}


// ���TNB����һ��Ҫtmd�ĸ㶮, ����
vec3 getNormalFromMap()
{
	vec3 tangentNormal = texture(normal_map, TexCoords).xyz * 2.0 - 1.0;

	vec3 Q1 = dFdx(WorldPos);
	vec3 Q2 = dFdy(WorldPos);
	vec2 st1 = dFdx(TexCoords);
	vec2 st2 = dFdy(TexCoords);

	vec3 N = normalize(Normal);
	vec3 T = normalize(Q1 * st2.t - Q2 * st1.t);
	vec3 B = -normalize(cross(N, T));
	mat3 TBN = mat3(T, B, N);

	return normalize(TBN * tangentNormal);
}

void main()
{

	vec3 albedo = pow(texture(albedo_map, TexCoords).rgb, vec3(2.2));
	float metallic = texture(metallic_map, TexCoords).r;
	float roughness = texture(roughness_map, TexCoords).r;
	float ao = texture(ao_map, TexCoords).r;


	vec3 N = getNormalFromMap();
	vec3 V = normalize(cameraPos - WorldPos);

	// reflectance equation
	vec3 Lo = vec3(0.0);
	for (int i = 0; i < 4; i++)
	{
		vec3 L = normalize(lightPosition[i] - WorldPos);
		vec3 H = normalize(L + V);

		float distance = length(lightPosition[i] - WorldPos);
		float attenuation = 1.0 / (distance * distance);
		// ���Ǹ��ݾ��������������ɫ
		vec3 radiance = lightColors[i] * attenuation;

		vec3 F = fresnel(H, V, albedo, metallic);
		float NDF = normal_distributon(N, H, roughness);
		float G = geometry(N, V, L, roughness);


		vec3 nominator = NDF * G * F;
		float denominator = 4 * max(dot(V, N), 0.0) * max(dot(L, N), 0.0) + 0.001; // �����ĸΪ0

		vec3 specular = nominator / denominator;


		vec3 ks = F;
		vec3 kd = vec3(1.0) - ks;
		kd *= 1.0 - metallic;

		// N dot LӦ����cosThe
		float NdotL = max(dot(N, L), 0.0);
		Lo += (specular + kd * albedo / PI) * radiance * NdotL;

	}

	// ����һ��������
	vec3 ambient = vec3(0.03) * albedo * ao;
	vec3 color = ambient + Lo;


	// ٤�����
	color = color / (color + vec3(1.0));
	color = pow(color, vec3(1.0 / 2.2));

	FragColor = vec4(color, 1.0);
}