//#include"primer/glsl/Glsl.h"
//#include"primer/texture/Texture.h"
//#include"primer/transform/Transform.h"
//#include"primer/cooridinate/Cooridinate.h"
//#include"primer/camera/CameraLession.h"
//#include"light/color/Color.h"
//#include"light/base_light/BaseLight.h"
//#include"light/material/Material.h"
//#include"light/light_texture/LightTexture.h"
//#include"light/cast_light/CastLight.h"
//#include"light/multiple_lights/MultipleLights.h"
//#include"advance/frame_buffer/FrameBuffer.h"

#include"advance/cube_map/CubeMap.h"
//#include"advanced_lighting/shadow/shadow_mapping/ShadowMapping.h"
//include"advanced_lighting/point_shadow/PointShadow.h"
//#include"advanced_lighting/normal_mapping/NormalMapping.h"
//#include"advanced_lighting/parallax_mapping/ParallaxMapping.h"
//#include"advanced_lighting/hdr/hdr.h"
//#include"advanced_lighting/bloom/bloom.h"
//#include"advanced_lighting/deffered_shading/DefferedShading.h"
//#include"load_model/ModelRun.h"
//#include"pbr/lighting/PbrLighting.h"
#include"pbr/ibl/ibl_fd/IblFd.h"


int main() {
	IblFd glsl;
	return glsl.run();
}
