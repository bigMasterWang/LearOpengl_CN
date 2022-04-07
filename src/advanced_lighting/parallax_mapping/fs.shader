#version 460 core
out vec4 FragColor;



in VS_OUT{
	vec3 FragPos;
	vec2 TexCoords;
	vec3 TangentLightPos;
	vec3 TangentViewPos;
	vec3 TangentFragPos;
} fs_in;


uniform sampler2D diffuse_texture;
uniform sampler2D normal_texture;
uniform sampler2D depth_texture;

uniform float height_scale;
uniform int use_phone;

vec2 ParallaxMapping(vec2 texCoords, vec3 viewDir)
{

	// number of depth layers
	const float minLayers = 8;
	const float maxLayers = 32;
	// float numLayers = mix(maxLayers, minLayers, abs(dot(vec3(0.0, 0.0, 1.0), viewDir)));
	float numLayers = 32;
	// calculate the size of each layer
	float layerDepth = 1.0 / numLayers;
	// depth of current layer
	float currentLayerDepth = 0.0;
	// the amount to shift the texture coordinates per layer (from vector P)
	vec2 P = viewDir.xy * height_scale;
	vec2 deltaTexCoords = P / numLayers;
	vec2  currentTexCoords = texCoords;
	float currentDepthMapValue = texture(depth_texture, currentTexCoords).r;

	while (currentLayerDepth < currentDepthMapValue)
	{
		// shift texture coordinates along direction of P
		currentTexCoords -= deltaTexCoords;
		// get depthmap value at current texture coordinates
		currentDepthMapValue = texture(depth_texture, currentTexCoords).r;
		// get depth of next layer
		currentLayerDepth += layerDepth;
	}

	// return texCoords - currentTexCoords;
	return currentTexCoords;


	// 计算前一个的纹理坐标
	vec2 prevTexCoords = currentTexCoords + deltaTexCoords;
	// 负
	float currDiffDepth = currentDepthMapValue - currentLayerDepth;
	// 正
	float prevDiffDepth = texture(depth_texture, prevTexCoords).r - (currentLayerDepth - layerDepth);
	// 然后进行线性插值
	float prevWeight = prevDiffDepth / (prevDiffDepth - currDiffDepth);
	return prevTexCoords * prevWeight + (1 - prevWeight) * currentTexCoords;





	//// 用1去减， 高度贴图就变成了深度贴图
	//float height = texture(depth_texture, texCoords).r;
	//// xy / z 是为了在uv平面上， 获取到标准的二维向量
	//vec2 p = viewDir.xy / viewDir.z * (height * height_scale);
	//return texCoords - p;
}

void main()
{
	vec3 view_dir = normalize(fs_in.TangentViewPos - fs_in.TangentFragPos);
	vec2 tex_coords = fs_in.TexCoords;
	if (use_phone == 1)
	{
		tex_coords = ParallaxMapping(fs_in.TexCoords, view_dir);
	}
	if (tex_coords.x > 1.0 || tex_coords.y > 1.0 || tex_coords.x < 0.0 || tex_coords.y < 0.0)
		discard;


	vec3 normal = texture(normal_texture, tex_coords).rgb;
	normal = normalize(normal * 2.0 - 1.0);

	// get diffuse color
	vec3 color = texture(diffuse_texture, tex_coords).rgb;
	// ambient
	vec3 ambient = 0.1 * color;
	// diffuse
	vec3 lightDir = normalize(fs_in.TangentLightPos - fs_in.TangentFragPos);
	float diff = max(dot(lightDir, normal), 0.0);
	vec3 diffuse = diff * color;
	// specular
	vec3 viewDir = normalize(fs_in.TangentViewPos - fs_in.TangentFragPos);
	vec3 reflectDir = reflect(-lightDir, normal);
	vec3 halfwayDir = normalize(lightDir + viewDir);
	float spec = pow(max(dot(normal, halfwayDir), 0.0), 32.0);

	vec3 specular = vec3(0.2) * spec;
	FragColor = vec4(ambient + diffuse + specular, 1.0);
}
