#version 460 core
//out vec4 FragColor;
// 两个帧缓冲
layout(location = 0) out vec4 FragColor;
layout(location = 1) out vec4 BrightColor;

// 四个点光源的位置
uniform vec3 light_color;

void main()
{
	FragColor = vec4(light_color, 1.0);
	float brightness = dot(FragColor.rgb, vec3(0.33, 0.33, 0.33));
	if (brightness >= 3.0)
		BrightColor = vec4(FragColor.rgb, 1.0);
}