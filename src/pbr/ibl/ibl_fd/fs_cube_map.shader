#version 460 core
out vec4 FragColor;
in vec3 localPos;

uniform sampler2D hdr_texture;


const vec2 invAtan = vec2(0.1591, 0.3183);
vec2 SampleSphericalMap(vec3 v)
{
	vec2 uv = vec2(atan(v.z, v.x), asin(v.y));
	uv *= invAtan;
	uv += 0.5;
	return uv;
}


//????????ͼ??cubemap
void main()
{
	vec2 uv = SampleSphericalMap(normalize(localPos)); // make sure to normalize localPos
	vec3 color = texture(hdr_texture, uv).rgb;

	FragColor = vec4(color, 1.0);
}
