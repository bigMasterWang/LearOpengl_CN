#version 460 core
out vec4 FragColor;


in VS_OUT{
	vec3 frag_pos;
	vec3 normal;
	vec2 texcoords;
} fs_in;

uniform sampler2D object_texture;
uniform samplerCube depthMap;
uniform vec3 light_pos;
uniform vec3 view_pos;
uniform float far_plane;

// 可能错误的原因
// 1. frag_pos错误

float shadow_calculation(vec3 frag_pos)
{
	vec3 fragToLight = frag_pos - light_pos;
	//float closestDepth = texture(depthMap, fragToLight).r;
	//closestDepth *= far_plane;

	float currentDepth = length(fragToLight);
	//float bias = 0.005;
	//float shadow = currentDepth - bias > closestDepth ? 1.0 : 0.0;


	//FragColor = vec4(vec3(closestDepth / far_plane), 1.0);

	//return shadow;
	vec3 sampleOffsetDirections[20] = vec3[]
	(
		vec3(1, 1, 1), vec3(1, -1, 1), vec3(-1, -1, 1), vec3(-1, 1, 1),
		vec3(1, 1, -1), vec3(1, -1, -1), vec3(-1, -1, -1), vec3(-1, 1, -1),
		vec3(1, 1, 0), vec3(1, -1, 0), vec3(-1, -1, 0), vec3(-1, 1, 0),
		vec3(1, 0, 1), vec3(-1, 0, 1), vec3(1, 0, -1), vec3(-1, 0, -1),
		vec3(0, 1, 1), vec3(0, -1, 1), vec3(0, -1, -1), vec3(0, 1, -1)
		);

	float shadow = 0.0;
	float bias = 0.15;
	int samples = 20;
	float viewDistance = length(view_pos - frag_pos);
	float diskRadius = 0.05;
	for (int i = 0; i < samples; ++i)
	{
		float closestDepth = texture(depthMap, fragToLight + sampleOffsetDirections[i] * diskRadius).r;
		closestDepth *= far_plane;   // Undo mapping [0;1]
		if (currentDepth - bias > closestDepth)
			shadow += 1.0;
	}
	shadow /= float(samples);
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

	float shadow = shadow_calculation(fs_in.frag_pos);

	// 为什么要乘上多次的color？？
	vec3 lighting = (ambient + (1 - shadow) * (diffuse + specular)) * color;
	//vec3 lighting = (ambient + diffuse + specular) * color;

	FragColor = vec4(lighting, 1.0);



}