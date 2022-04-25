#version 460 core
out vec4 FragColor;

uniform sampler2D frame_texture;
uniform sampler2D blur_texture;
in vec2 TexCoords;
uniform bool use_blur;

void main()
{
	if (use_blur)
	{
		const float gamma = 2.2;
		vec3 hdrColor = texture(frame_texture, TexCoords).rgb;
		hdrColor += texture(blur_texture, TexCoords).rgb;


		//// Reinhard色调映射
		//vec3 mapped = hdrColor / (hdrColor + vec3(1.0));
		//// Gamma校正
		//mapped = pow(mapped, vec3(1.0 / gamma));
		//FragColor = vec4(mapped, 1.0);

		// 曝光色调映射
		float exposure = 1.0;
		vec3 mapped = vec3(1.0) - exp(-hdrColor * exposure);
		// Gamma校正
		mapped = pow(mapped, vec3(1.0 / gamma));
		FragColor = vec4(mapped, 1.0);

		FragColor = vec4(hdrColor, 1.0);
	}
	else
	{
		FragColor = texture(frame_texture, TexCoords);
	}
}