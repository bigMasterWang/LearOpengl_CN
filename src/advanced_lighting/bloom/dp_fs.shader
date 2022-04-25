#version 460 core
//out vec4 FragColor;
layout(location = 0) out vec4 FragColor;
layout(location = 1) out vec4 BrightColor;

in VS_OUT{
	vec3 frag_pos;
	vec3 normal;
} fs_in;
in vec2 TexCoords;
uniform sampler2D frame_texture;
uniform vec3 view_pos;

// 四个点光源的位置
uniform vec3 light_colors[4];
uniform vec3 light_pos[4];



void main()
{
	vec3 color = texture(frame_texture, TexCoords).rgb;
	vec3 normal = normalize(fs_in.normal);

	vec3 final_color = vec3(0.0);
	for (int i = 0; i < 4; i++)
	{
		vec3 light_color = light_colors[i];
		// ambient
		vec3 ambient = 0.15 * color;

		float distance = length(fs_in.frag_pos - light_pos[i]);

		// diffuse
		vec3 light_dir = normalize(light_pos[i] - fs_in.frag_pos);
		float diff = max(dot(light_dir, normal), 0.0);
		vec3 diffuse = diff * light_color / distance;

		// specular
		vec3 view_dir = normalize(view_pos - fs_in.frag_pos);
		vec3 halfway_dir = normalize(view_dir + light_dir);
		float spec = pow(max(dot(normal, halfway_dir), 0.0), 64.0);
		vec3 specular = spec * light_color / distance;

		vec3 f_color = vec3(ambient + diffuse + specular) * color;
		final_color += f_color;
	}
	FragColor = vec4(final_color, 1.0);
	float brightness = dot(FragColor.rgb, vec3(0.33, 0.33, 0.33));
	if (brightness >= 3.0)
		BrightColor = vec4(FragColor.rgb, 1.0);
}