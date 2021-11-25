#pragma once
#include<glfw3.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

class Camera
{
private:
	float lastX = 400, lastY = 300;
	bool firstMouse = true;
	float yaw = 180.0f, pitch = 0.0f;
	//’’œ‡ª˙ Ù–‘
	glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
	glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
public:
	Camera(float window_width, float window_height);
	~Camera();
	glm::mat4 get_look_at_matrix();
	void input_callback(GLFWwindow* window, float delta_time);
	void mouse_callback(GLFWwindow* window, double xpos, double ypos);
	inline glm::vec3 get_pos() { return cameraPos; }
};


void global_mouse_callback(GLFWwindow* window, double xpos, double ypos);
