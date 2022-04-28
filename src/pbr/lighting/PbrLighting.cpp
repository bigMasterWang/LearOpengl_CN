#include "PbrLighting.h"
#include<glad/glad.h>
#include<glfw3.h>
#include<iostream>
#include"tools/shader.h"
#include"tools/stb_image.h"
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include"tools/Camera.h"
#include<vector>
#include<sstream>
#include"tools/common_tools.h"
#include"load_model/Model.h"
int PbrLighting::run()

{
	// settings
	const unsigned int SCR_WIDTH = 800;
	const unsigned int SCR_HEIGHT = 600;
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	// ø™∆Ùøπæ‚≥›
	glfwWindowHint(GLFW_SAMPLES, 4);

	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	// Shader pbr_shader("src/pbr/lighting/vs.shader", "src/pbr/lighting/fs.shader");
	Shader pbr_shader("src/pbr/lighting/vs_texture.shader", "src/pbr/lighting/fs_texture.shader");

	unsigned int normal_texture = create_texture("E:/VSProjects/LearnOpengl_CN/res/pbr/ornate-brass_normal-dx.png");
	unsigned int albedo_texture = create_texture("E:/VSProjects/LearnOpengl_CN/res/pbr/ornate-brass_albedo.png");
	unsigned int metallic_texture = create_texture("E:/VSProjects/LearnOpengl_CN/res/pbr/ornate-brass_metallic.png");
	unsigned int roughness_texture = create_texture("E:/VSProjects/LearnOpengl_CN/res/pbr/ornate-brass_roughness.png");
	unsigned int ao_texture = create_texture("E:/VSProjects/LearnOpengl_CN/res/pbr/ornate-brass_ao.png");

	//unsigned int normal_texture = create_texture("E:/VSProjects/LearnOpengl_CN/res/pbr/rustediron1/rustediron2_normal.png");
	//unsigned int albedo_texture = create_texture("E:/VSProjects/LearnOpengl_CN/res/pbr/rustediron1/rustediron2_basecolor.png");
	//unsigned int metallic_texture = create_texture("E:/VSProjects/LearnOpengl_CN/res/pbr/rustediron1/rustediron2_metallic.png");
	//unsigned int roughness_texture = create_texture("E:/VSProjects/LearnOpengl_CN/res/pbr/rustediron1/rustediron2_roughness.png");
	//unsigned int ao_texture = create_texture("E:/VSProjects/LearnOpengl_CN/res/pbr/rustediron1/ornate-brass_ao.png");




	int index_count = 0;
	unsigned int sphere_vao;
	glGenVertexArrays(1, &sphere_vao);

	unsigned int vbo, ebo;
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ebo);

	std::vector<glm::vec3> positions;
	std::vector<glm::vec2> uv;
	std::vector<glm::vec3> normals;
	std::vector<unsigned int> indices;

	const unsigned int X_SEGMENTS = 64;
	const unsigned int Y_SEGMENTS = 64;
	const float PI = 3.14159265359f;
	for (unsigned int x = 0; x <= X_SEGMENTS; ++x)
	{
		for (unsigned int y = 0; y <= Y_SEGMENTS; ++y)
		{
			float xSegment = (float)x / (float)X_SEGMENTS;
			float ySegment = (float)y / (float)Y_SEGMENTS;
			float xPos = std::cos(xSegment * 2.0f * PI) * std::sin(ySegment * PI);
			float yPos = std::cos(ySegment * PI);
			float zPos = std::sin(xSegment * 2.0f * PI) * std::sin(ySegment * PI);

			positions.push_back(glm::vec3(xPos, yPos, zPos));
			uv.push_back(glm::vec2(xSegment, ySegment));
			normals.push_back(glm::vec3(xPos, yPos, zPos));
		}
	}

	bool oddRow = false;
	for (unsigned int y = 0; y < Y_SEGMENTS; ++y)
	{
		if (!oddRow) // even rows: y == 0, y == 2; and so on
		{
			for (unsigned int x = 0; x <= X_SEGMENTS; ++x)
			{
				indices.push_back(y * (X_SEGMENTS + 1) + x);
				indices.push_back((y + 1) * (X_SEGMENTS + 1) + x);
			}
		}
		else
		{
			for (int x = X_SEGMENTS; x >= 0; --x)
			{
				indices.push_back((y + 1) * (X_SEGMENTS + 1) + x);
				indices.push_back(y * (X_SEGMENTS + 1) + x);
			}
		}
		oddRow = !oddRow;
	}
	index_count = static_cast<unsigned int>(indices.size());

	std::vector<float> data;
	for (unsigned int i = 0; i < positions.size(); ++i)
	{
		data.push_back(positions[i].x);
		data.push_back(positions[i].y);
		data.push_back(positions[i].z);
		if (normals.size() > 0)
		{
			data.push_back(normals[i].x);
			data.push_back(normals[i].y);
			data.push_back(normals[i].z);
		}
		if (uv.size() > 0)
		{
			data.push_back(uv[i].x);
			data.push_back(uv[i].y);
		}
	}
	glBindVertexArray(sphere_vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), &data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
	unsigned int stride = (3 + 2 + 3) * sizeof(float);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride, (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, stride, (void*)(6 * sizeof(float)));




	// À„≥ˆ delta_time
	float last_frame_time = 0.0f;
	float delta_time = 0.0f;
	float current_time = 0.0f;
	// “˛≤ÿ Û±Í
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	//  Û±Í ‰»Î
	extern Camera my_camera;
	glfwSetCursorPosCallback(window, global_mouse_callback);

	glm::mat4 projection_matrix = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.01f, 1000.0f);


	//glm::vec3 lightPositions[] = {
	//	glm::vec3(-10.0f,  10.0f, 10.0f),
	//	glm::vec3(10.0f,  10.0f, 10.0f),
	//	glm::vec3(-10.0f, -10.0f, 10.0f),
	//	glm::vec3(10.0f, -10.0f, 10.0f),
	//};

	//glm::vec3 lightColors[] = {
	//	glm::vec3(300.0f, 300.0f, 300.0f),
	//	glm::vec3(300.0f, 300.0f, 300.0f),
	//	glm::vec3(300.0f, 300.0f, 300.0f),
	//	glm::vec3(300.0f, 300.0f, 300.0f)
	//};

	glm::vec3 lightPositions[] = {
	   glm::vec3(0.0f, 0.0f, 10.0f),
	};
	glm::vec3 lightColors[] = {
		glm::vec3(1500.0f, 1500.0f, 1500.0f),
	};

	pbr_shader.bind();
	glm::vec3 albedo = glm::vec3(0.5f, 0.0f, 0.0f);
	pbr_shader.set_vec3("albedo", &albedo);
	pbr_shader.set_float("ao", 1.0f);

	while (!glfwWindowShouldClose(window))
	{

		current_time = glfwGetTime();
		delta_time = current_time - last_frame_time;
		last_frame_time = current_time;
		my_camera.input_callback(window, delta_time);

		glEnable(GL_DEPTH_TEST);
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		pbr_shader.bind();
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, normal_texture);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, albedo_texture);
		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, metallic_texture);
		glActiveTexture(GL_TEXTURE3);
		glBindTexture(GL_TEXTURE_2D, roughness_texture);
		glActiveTexture(GL_TEXTURE4);
		glBindTexture(GL_TEXTURE_2D, ao_texture);
		pbr_shader.set_int("normal_map", 0);
		pbr_shader.set_int("albedo_map", 1);
		pbr_shader.set_int("metallic_map", 2);
		pbr_shader.set_int("roughness_map", 3);
		pbr_shader.set_int("ao_map", 4);

		glm::mat4 view_matrix = my_camera.get_look_at_matrix();
		glm::vec3 view_pos = my_camera.get_pos();
		pbr_shader.set_mat4("projection", &projection_matrix);
		pbr_shader.set_mat4("view", &view_matrix);
		pbr_shader.set_vec3("cameraPos", &my_camera.get_pos());


		int nrRows = 7;
		int nrColumns = 7;
		float spacing = 2.5;




		for (int row = 0; row < nrRows; ++row)
		{
			pbr_shader.set_float("metallic", (float)row / (float)nrRows);
			for (int col = 0; col < nrColumns; ++col)
			{
				// we clamp the roughness to 0.05 - 1.0 as perfectly smooth surfaces (roughness of 0.0) tend to look a bit off
				// on direct lighting.
				pbr_shader.set_float("roughness", glm::clamp((float)col / (float)nrColumns, 0.05f, 1.0f));

				glm::mat4 model = glm::mat4(1.0f);
				model = glm::translate(model, glm::vec3(
					(col - (nrColumns / 2)) * spacing,
					(row - (nrRows / 2)) * spacing,
					0.0f
				));
				pbr_shader.set_mat4("model", &model);
				glBindVertexArray(sphere_vao);
				glDrawElements(GL_TRIANGLE_STRIP, index_count, GL_UNSIGNED_INT, 0);
			}
		}


		// render light source (simply re-render sphere at light positions)
		// this looks a bit off as we use the same shader, but it'll make their positions obvious and 
		// keeps the codeprint small.
		for (unsigned int i = 0; i < sizeof(lightPositions) / sizeof(lightPositions[0]); ++i)
		{
			//glm::vec3 newPos = lightPositions[i] + glm::vec3(sin(glfwGetTime() * 5.0) * 5.0, 0.0, 0.0);
			glm::vec3 newPos = lightPositions[i];
			pbr_shader.set_vec3(("lightPosition[" + std::to_string(i) + "]").c_str(), &newPos);
			pbr_shader.set_vec3(("lightColors[" + std::to_string(i) + "]").c_str(), &lightColors[i]);

			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, newPos);
			model = glm::scale(model, glm::vec3(0.5f));
			pbr_shader.set_mat4("model", &model);
			glBindVertexArray(sphere_vao);
			glDrawElements(GL_TRIANGLE_STRIP, index_count, GL_UNSIGNED_INT, 0);
		}

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}
