#version 460 core
out vec4 FragColor;

uniform sampler2D blur_texture;
in vec2 TexCoords;

uniform bool horizontal;
float weight[5] = float[](0.2270270270, 0.1945945946, 0.1216216216, 0.0540540541, 0.0162162162);

void main()
{
	vec2 tex_offset = 1.0 / textureSize(blur_texture, 0);
	vec3 final_color = texture(blur_texture, TexCoords).rgb * weight[0];
	if (horizontal)
	{
		for (int i = 1; i < 5; i++)
		{
			final_color += texture(blur_texture, TexCoords + vec2(tex_offset.x * i, 0.0)).rgb * weight[i];
			final_color += texture(blur_texture, TexCoords - vec2(tex_offset.x * i, 0.0)).rgb * weight[i];
		}
	}
	else
	{
		for (int i = 1; i < 5; i++)
		{
			final_color += texture(blur_texture, TexCoords + vec2(0.0, tex_offset.y * i)).rgb * weight[i];
			final_color += texture(blur_texture, TexCoords - vec2(0.0, tex_offset.y * i)).rgb * weight[i];
		}
	}
	FragColor = vec4(final_color, 1.0);
}