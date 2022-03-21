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

#include"advance/frame_buffer/FrameBuffer.h"
#include"advanced_lighting/shadow/shadow_mapping/ShadowMapping.h"

int main() {
	ShadowMapping glsl;
	return glsl.run();
}
