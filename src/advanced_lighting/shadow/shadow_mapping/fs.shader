#version 460 core
out vec4 FragColor;


in VS_OUT{
	vec3 frag_pos;
	vec3 normal;
	vec2 texcoords;
	vec4 light_space_frag_pos;
} fs_in;

uniform sampler2D shadow_texture;
uniform sampler2D object_texture;
uniform vec3 light_pos;
uniform vec3 view_pos;


float shadow_calculation(vec4 light_space_frag_pos)
{
	// 以w为单位1， -1~1
	vec3 projecoords = light_space_frag_pos.xyz / light_space_frag_pos.w;
	// 转换到0~1
	projecoords = projecoords * 0.5 + 0.5;
	//再从深度贴图中取值， 用光源视角下的坐标进行取值
	//为什么要使用r？？
	float depth = texture(shadow_texture, projecoords.xy).r;
	float current_depth = projecoords.z;

	float bias = 0.005;

	//到这里就简单了， 如果大于深度，就是在阴影中， 不是就是正常
	float shadow = current_depth - bias > depth ? 1.0 : 0.0;
	if (projecoords.z > 1.0)
		shadow = 0.0;


	vec2 texelSize = 1.0 / textureSize(shadow_texture, 0);
	for (int x = -1; x <= 1; ++x)
	{
		for (int y = -1; y <= 1; ++y)
		{
			float pcfDepth = texture(shadow_texture, projecoords.xy + vec2(x, y) * texelSize).r;
			shadow += current_depth - bias > pcfDepth ? 1.0 : 0.0;
		}
	}
	shadow /= 9.0;

	return shadow;
}



void main()
{
	vec3 color = texture(object_texture, fs_in.texcoords).rgb;
	vec3 normal = normalize(fs_in.normal);
	vec3 light_color = vec3(1.0);


	// ambient
	vec3 ambient = 0.15 * color;

	// diffuse
	vec3 light_dir = normalize(light_pos - fs_in.frag_pos);
	float diff = max(dot(light_dir, normal), 0.0);
	vec3 diffuse = diff * light_color;

	// specular
	vec3 view_dir = normalize(view_pos - fs_in.frag_pos);
	vec3 halfway_dir = normalize(view_dir + light_dir);
	float spec = pow(max(dot(normal, halfway_dir), 0.0), 64.0);
	vec3 specular = spec * light_color;

	float shadow = shadow_calculation(fs_in.light_space_frag_pos);

	// 为什么要乘上多次的color？？
	vec3 lighting = (ambient + (1 - shadow) * (diffuse + specular)) * color;

	FragColor = vec4(lighting, 1.0);



}