#version 460 core
out vec4 FragColor;

in vec3 fragment_normal;
in vec3 fragment_position;

uniform vec3 camera_pos;
uniform samplerCube sky_texture;


void main()
{
   
    vec3 look_dir = normalize(fragment_position - camera_pos);
    // ∑¥…‰
    // vec3 color_dir = reflect(look_dir, normalize(fragment_normal));

    // ’€…‰
    float ratio = 1.00 / 1.52;
    vec3 color_dir = refract(look_dir, normalize(fragment_normal), ratio);

    FragColor = vec4(texture(sky_texture, color_dir).rgb, 1.0);
} 