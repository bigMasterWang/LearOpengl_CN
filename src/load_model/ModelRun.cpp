#include "ModelRun.h"
#include<glad/glad.h>
#include<glfw3.h>
#include"Model.h"
#include<iostream>
#include"tools/stb_image.h"
#include"tools/Camera.h"
#include"glm.hpp"


int ModelRun::run()
{
	// settings
	const unsigned int SCR_WIDTH = 800;
	const unsigned int SCR_HEIGHT = 600;


	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "my son fuyu", NULL, NULL);
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

	// stbi_set_flip_vertically_on_load(true);


	Shader ourShader("src/load_model/model_loading.vs", "src/load_model/model_loading.fs");
	Shader single_shader("src/load_model/model_loading.vs", "src/load_model/single_color.fs");
	Model ourModel("res/objects/nanosuit.obj");

	Model ourModel2("res/objects/nanosuit.obj");


	//float vertices[] = {
	//	// pos, normal_vec, texture
	//	-0.5f, -0.5f, -0.5f,   0.0f, 0.0f, -1.0f,   0.0f, 0.0f,
	//	 0.5f, -0.5f, -0.5f,   0.0f, 0.0f, -1.0f,   1.0f, 0.0f,
	//	 0.5f,  0.5f, -0.5f,   0.0f, 0.0f, -1.0f,   1.0f, 1.0f,
	//	 0.5f,  0.5f, -0.5f,   0.0f, 0.0f, -1.0f,   1.0f, 1.0f,
	//	-0.5f,  0.5f, -0.5f,   0.0f, 0.0f, -1.0f,   0.0f, 1.0f,
	//	-0.5f, -0.5f, -0.5f,   0.0f, 0.0f, -1.0f,   0.0f, 0.0f,
	//	-0.5f, -0.5f,  0.5f,   0.0f, 0.0f, 1.0f,    0.0f, 0.0f,
	//	 0.5f, -0.5f,  0.5f,   0.0f, 0.0f, 1.0f,    1.0f, 0.0f,
	//	 0.5f,  0.5f,  0.5f,   0.0f, 0.0f, 1.0f,    1.0f, 1.0f,
	//	 0.5f,  0.5f,  0.5f,   0.0f, 0.0f, 1.0f,    1.0f, 1.0f,
	//	-0.5f,  0.5f,  0.5f,   0.0f, 0.0f, 1.0f,    0.0f, 1.0f,
	//	-0.5f, -0.5f,  0.5f,   0.0f, 0.0f, 1.0f,    0.0f, 0.0f,

	//	-0.5f,  0.5f,  0.5f,   -1.0f, 0.0f, 0.0f,   1.0f, 0.0f,
	//	-0.5f,  0.5f, -0.5f,   -1.0f, 0.0f, 0.0f,   1.0f, 1.0f,
	//	-0.5f, -0.5f, -0.5f,   -1.0f, 0.0f, 0.0f,   0.0f, 1.0f,
	//	-0.5f, -0.5f, -0.5f,   -1.0f, 0.0f, 0.0f,   0.0f, 1.0f,
	//	-0.5f, -0.5f,  0.5f,   -1.0f, 0.0f, 0.0f,   0.0f, 0.0f,
	//	-0.5f,  0.5f,  0.5f,   -1.0f, 0.0f, 0.0f,   1.0f, 0.0f,

	//	 0.5f,  0.5f,  0.5f,   1.0f, 0.0f, 0.0f,    1.0f, 0.0f,
	//	 0.5f,  0.5f, -0.5f,   1.0f, 0.0f, 0.0f,    1.0f, 1.0f,
	//	 0.5f, -0.5f, -0.5f,   1.0f, 0.0f, 0.0f,    0.0f, 1.0f,
	//	 0.5f, -0.5f, -0.5f,   1.0f, 0.0f, 0.0f,    0.0f, 1.0f,
	//	 0.5f, -0.5f,  0.5f,   1.0f, 0.0f, 0.0f,    0.0f, 0.0f,
	//	 0.5f,  0.5f,  0.5f,   1.0f, 0.0f, 0.0f,    1.0f, 0.0f,

	//	-0.5f, -0.5f, -0.5f,   0.0f, -1.0f, 0.0f,   0.0f, 1.0f,
	//	 0.5f, -0.5f, -0.5f,   0.0f, -1.0f, 0.0f,   1.0f, 1.0f,
	//	 0.5f, -0.5f,  0.5f,   0.0f, -1.0f, 0.0f,   1.0f, 0.0f,
	//	 0.5f, -0.5f,  0.5f,   0.0f, -1.0f, 0.0f,   1.0f, 0.0f,
	//	-0.5f, -0.5f,  0.5f,   0.0f, -1.0f, 0.0f,   0.0f, 0.0f,
	//	-0.5f, -0.5f, -0.5f,   0.0f, -1.0f, 0.0f,   0.0f, 1.0f,

	//	-0.5f,  0.5f, -0.5f,   0.0f, 1.0f, 0.0f,    0.0f, 1.0f,
	//	 0.5f,  0.5f, -0.5f,   0.0f, 1.0f, 0.0f,    1.0f, 1.0f,
	//	 0.5f,  0.5f,  0.5f,   0.0f, 1.0f, 0.0f,    1.0f, 0.0f,
	//	 0.5f,  0.5f,  0.5f,   0.0f, 1.0f, 0.0f,    1.0f, 0.0f,
	//	-0.5f,  0.5f,  0.5f,   0.0f, 1.0f, 0.0f,    0.0f, 0.0f,
	//	-0.5f,  0.5f, -0.5f,   0.0f, 1.0f, 0.0f,    0.0f, 1.0f,
	//};
	//unsigned int VAO, VBO;
	//glGenVertexArrays(1, &VAO);
	//glBindVertexArray(VAO);
	//glGenBuffers(1, &VBO);
	//glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	//// 设置layout
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), 0);
	//glEnableVertexAttribArray(0);
	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	//glEnableVertexAttribArray(1);
	//glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	//glEnableVertexAttribArray(2);


	// 开启深度测试
	glEnable(GL_DEPTH_TEST);



	// 算出 delta_time
	float last_frame_time = 0.0f;
	float delta_time = 0.0f;
	float current_time = 0.0f;


	// 隐藏鼠标
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// 鼠标输入
	extern Camera my_camera;
	glfwSetCursorPosCallback(window, global_mouse_callback);


	glm::mat4 projection_matrix = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		// glClear(GL_COLOR_BUFFER_BIT);
		// 每次渲染之前清除深度缓冲, 模板缓冲
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

		// 计算出delta_time
		current_time = glfwGetTime();
		delta_time = current_time - last_frame_time;
		last_frame_time = current_time;

		// 处理移动
		my_camera.input_callback(window, delta_time);


		glEnable(GL_DEPTH_TEST);
		glEnable(GL_STENCIL_TEST);
		glStencilMask(0xFF);

		//glStencilFunc(GL_ALWAYS, 1, 0xFF);
		//将模板值设置为glStencilFunc函数设置的ref值
		//glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

		glm::mat4 view = my_camera.get_look_at_matrix();
		{
			ourShader.set_mat4("projection", &projection_matrix);
			ourShader.set_mat4("view", &view);

			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
			model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
			ourShader.set_mat4("model", &model);
			ourModel.draw(ourShader);
		}

		//// 禁止模板写入
		//glStencilMask(0x00);
		////禁止深度测试
		//glDisable(GL_DEPTH_TEST);
		//// 只画不等于1的
		//glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
		//{
		//	single_shader.set_mat4("projection", &projection_matrix);
		//	single_shader.set_mat4("view", &view);

		//	glm::mat4 model = glm::mat4(1.0f);
		//	model = glm::translate(model, glm::vec3(0.0f, -0.007f, 0.0f));
		//	model = glm::scale(model, glm::vec3(0.3015f, 0.3015f, 0.3015f));
		//	single_shader.set_mat4("model", &model);
		//	ourModel2.draw(single_shader);
		//}
		//// 为什么要在这个地方重新开启???
		//// 开启模板写入
		//glStencilMask(0xFF);
		//// 开启深度测试
		//glEnable(GL_DEPTH_TEST);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}
