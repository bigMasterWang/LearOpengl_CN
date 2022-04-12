#version 460 core
out vec4 FragColor;

uniform sampler2D frame_texture;
in vec2 TexCoords;

void main()
{

	const float gamma = 2.2;
	vec3 hdrColor = texture(frame_texture, TexCoords).rgb;

	float exposure = 1.0;

	//FragColor = vec4(hdrColor, 1.0);

	// Reinhardɫ��ӳ��
	vec3 mapped = hdrColor / (hdrColor + vec3(1.0));
	// GammaУ��
	mapped = pow(mapped, vec3(1.0 / gamma));
	FragColor = vec4(mapped, 1.0);

	//// �ع�ɫ��ӳ��
	//vec3 mapped = vec3(1.0) - exp(-hdrColor * exposure);
	//// GammaУ��
	//mapped = pow(mapped, vec3(1.0 / gamma));
	//FragColor = vec4(mapped, 1.0);
}