#version 460 core
out vec4 FragColor;

uniform sampler2D frame_texture;
uniform sampler2D normal_texture;
uniform sampler2D position_specular_texture;
in vec2 TexCoords;


uniform vec3 view_pos;

// 四个点光源的位置
uniform int light_number;
uniform vec3 light_colors[32];
uniform vec3 light_pos[32];





void main()
{
	vec3 color = texture(frame_texture, TexCoords).rgb;
	vec3 normal = texture(normal_texture, TexCoords).rgb;
	// 计算光照的模型的位置
	vec3 frag_pos = texture(position_specular_texture, TexCoords).rgb;

	vec3 final_color = vec3(0.0);
	for (int i = 0; i < light_number; i++)
	{
		vec3 light_color = light_colors[i];
		// ambient
		vec3 ambient = 0.15 * color;

		float distance = length(frag_pos - light_pos[i]);

		// diffuse
		vec3 light_dir = normalize(light_pos[i] - frag_pos);
		float diff = max(dot(light_dir, normal), 0.0);
		vec3 diffuse = diff * light_color / pow(distance, 2);

		// specular
		vec3 view_dir = normalize(view_pos - frag_pos);
		vec3 halfway_dir = normalize(view_dir + light_dir);
		float spec = pow(max(dot(normal, halfway_dir), 0.0), 64.0);
		vec3 specular = spec * light_color / pow(distance, 2);

		vec3 f_color = vec3(ambient + diffuse + specular) * color;
		final_color += f_color;
	}
	FragColor = vec4(final_color, 1.0);

	//const float gamma = 2.2;
	//vec3 hdrColor = final_color;
	//float exposure = 1.0;
	////FragColor = vec4(hdrColor, 1.0);
	//// Reinhard色调映射
	//vec3 mapped = hdrColor / (hdrColor + vec3(1.0));
	//// Gamma校正
	//mapped = pow(mapped, vec3(1.0 / gamma));
	////// 曝光色调映射
	////vec3 mapped = vec3(1.0) - exp(-hdrColor * exposure);
	////// Gamma校正
	////mapped = pow(mapped, vec3(1.0 / gamma));
	//FragColor = vec4(mapped, 1.0);
}