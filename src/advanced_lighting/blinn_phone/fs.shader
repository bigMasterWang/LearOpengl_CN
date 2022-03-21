#version 460 core
out vec4 FragColor;

uniform sampler2D floorTexture;
uniform vec3 view_pos;
uniform vec3 light_pos;


in vec2 in_tex;
in vec3 fragment_normal;
in vec3 fragment_pos;

uniform int use_phone;

void main()
{

    vec3 light_dir = normalize(light_pos - fragment_pos);

    vec3 object_color = texture(floorTexture, in_tex).rgb;
    // 环境光
    vec3 ambient = 0.2 * object_color;
    // 漫反射
    // 为什么漫反射的强度 和 normal 与 light_dir的夹角有关? 想不明白
    float diff = max(dot(light_dir, fragment_normal), 0.0);
    vec3 diff_color = diff * object_color;


    // 镜面反射
    float reflect_number = 0.0;
    if (use_phone == 1)
    {
        vec3 view_dir = normalize(view_pos - fragment_pos);
        vec3 reflect_dir = reflect(-light_dir, fragment_normal);
        reflect_number = pow(max(dot(view_dir, reflect_dir), 0.0), 8.0);
    }
    else
    {
        vec3 view_dir = normalize(view_pos - fragment_pos);
        vec3 halfway_dir = normalize(light_dir + view_dir);
        reflect_number = pow(max(dot(halfway_dir, fragment_normal), 0.0), 32.0);
    }

    vec3 reflect_color = reflect_number * object_color;

    FragColor = vec4(ambient + diff_color + reflect_color, 1.0);

}