#include"primer/glsl/Glsl.h"
#include"primer/texture/Texture.h"
#include"primer/transform/Transform.h"
#include"primer/cooridinate/Cooridinate.h"
#include"primer/camera/CameraLession.h"
#include"light/color/Color.h"
#include"light/base_light/BaseLight.h"
#include"light/material/Material.h"
#include"light/light_texture/LightTexture.h"
#include"light/cast_light/CastLight.h"
#include"light/multiple_lights/MultipleLights.h"

int main()
{
	MultipleLights glsl;
	return glsl.run();
}
