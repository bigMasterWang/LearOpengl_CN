#version 460 core
out vec4 FragColor;
in vec3 localPos;

uniform samplerCube cube_map_texture;


void main()
{
	vec3 envColor = texture(cube_map_texture, localPos).rgb;
	// HDR tonemap and gamma correct
	envColor = envColor / (envColor + vec3(1.0));
	envColor = pow(envColor, vec3(1.0 / 2.2));
	FragColor = vec4(envColor, 1.0);
}
