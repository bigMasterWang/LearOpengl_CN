#include "Camera.h"
#include<iostream>


Camera my_camera(800.0f, 600.0f);


Camera::Camera(float window_width, float window_height) : lastX(window_width / 2), lastY(window_height / 2)
{
}

Camera::~Camera()
{
}


void global_mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	my_camera.mouse_callback(window, xpos, ypos);
}


void Camera::mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos;
	lastX = xpos;
	lastY = ypos;

	float sensitivity = 0.05;
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	yaw += xoffset;
	pitch += yoffset;

	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;

	glm::vec3 front;
	front.x = sin(glm::radians(-yaw));
	front.y = sin(glm::radians(pitch));
	front.z = cos(glm::radians(-yaw)) * cos(glm::radians(pitch));
	cameraFront = glm::normalize(front);
	std::cout << cameraFront.x << ", " << cameraFront.y << "," << cameraFront.z << std::endl;
}

void Camera::input_callback(GLFWwindow* window, float delta_time)
{
	float cameraSpeed = 2.5f * delta_time; // adjust accordingly
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		cameraPos += cameraSpeed * cameraFront;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		cameraPos -= cameraSpeed * cameraFront;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
		cameraPos -= cameraSpeed * cameraUp;
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
		cameraPos += cameraSpeed * cameraUp;
}


glm::mat4 Camera::get_look_at_matrix()
{
	return glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
}
