#version 460 core
out vec4 FragColor;
in vec3 localPos;

uniform samplerCube cube_map_texture;
const float PI = 3.141592654;

void main()
{
	// the sample direction equals the hemisphere's orientation 
	vec3 normal = normalize(localPos);

	vec3 irradiance = vec3(0.0);

	vec3 up = vec3(0.0, 1.0, 0.0);
	vec3 right = cross(up, normal);
	up = cross(normal, right);

	float sampleDelta = 0.025;
	float nrSamples = 0.0;
	for (float phi = 0.0; phi < 2.0 * PI; phi += sampleDelta)
	{
		for (float theta = 0.0; theta < 0.5 * PI; theta += sampleDelta)
		{
			// spherical to cartesian (in tangent space)
			vec3 tangentSample = vec3(sin(theta) * cos(phi), sin(theta) * sin(phi), cos(theta));
			// tangent space to world
			vec3 sampleVec = tangentSample.x * right + tangentSample.y * up + tangentSample.z * normal;

			// * sin(theta)是为了方位角高是，分辨率低，提高贡献度， * cos(theta)是为了什么？？
			irradiance += texture(cube_map_texture, sampleVec).rgb * cos(theta) * sin(theta);
			nrSamples++;
		}
	}
	irradiance = PI * irradiance * (1.0 / float(nrSamples));
	FragColor = vec4(irradiance, 1.0);
}