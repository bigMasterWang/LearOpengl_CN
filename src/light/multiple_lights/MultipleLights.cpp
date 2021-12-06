#include "MultipleLights.h"
#include<glad/glad.h>
#include<glfw3.h>
#include<iostream>
#include"tools/shader.h"
#include"tools/stb_image.h"
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include"tools/Camera.h"


int MultipleLights::run()
{
	// settings
	const unsigned int SCR_WIDTH = 800;
	const unsigned int SCR_HEIGHT = 600;


	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
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


	float vertices[] = {
		// pos, texture, normal_vec
		-0.5f, -0.5f, -0.5f,   0.0f, 0.0f,   0.0f, 0.0f, -1.0f,
		 0.5f, -0.5f, -0.5f,   1.0f, 0.0f,   0.0f, 0.0f, -1.0f,
		 0.5f,  0.5f, -0.5f,   1.0f, 1.0f,   0.0f, 0.0f, -1.0f,
		 0.5f,  0.5f, -0.5f,   1.0f, 1.0f,   0.0f, 0.0f, -1.0f,
		-0.5f,  0.5f, -0.5f,   0.0f, 1.0f,   0.0f, 0.0f, -1.0f,
		-0.5f, -0.5f, -0.5f,   0.0f, 0.0f,   0.0f, 0.0f, -1.0f,

		-0.5f, -0.5f,  0.5f,   0.0f, 0.0f,   0.0f, 0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,   1.0f, 0.0f,   0.0f, 0.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,   1.0f, 1.0f,   0.0f, 0.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,   1.0f, 1.0f,   0.0f, 0.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,   0.0f, 1.0f,   0.0f, 0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,   0.0f, 0.0f,   0.0f, 0.0f, 1.0f,

		-0.5f,  0.5f,  0.5f,   1.0f, 0.0f,   -1.0f, 0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,   1.0f, 1.0f,   -1.0f, 0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,   0.0f, 1.0f,   -1.0f, 0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,   0.0f, 1.0f,   -1.0f, 0.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,   0.0f, 0.0f,   -1.0f, 0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,   1.0f, 0.0f,   -1.0f, 0.0f, 0.0f,

		 0.5f,  0.5f,  0.5f,   1.0f, 0.0f,   1.0f, 0.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,   1.0f, 1.0f,   1.0f, 0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,   0.0f, 1.0f,   1.0f, 0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,   0.0f, 1.0f,   1.0f, 0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,   0.0f, 0.0f,   1.0f, 0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,   1.0f, 0.0f,   1.0f, 0.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,   0.0f, 1.0f,   0.0f, -1.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,   1.0f, 1.0f,   0.0f, -1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,   1.0f, 0.0f,   0.0f, -1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,   1.0f, 0.0f,   0.0f, -1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,   0.0f, 0.0f,   0.0f, -1.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,   0.0f, 1.0f,   0.0f, -1.0f, 0.0f,

		-0.5f,  0.5f, -0.5f,   0.0f, 1.0f,   0.0f, 1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,   1.0f, 1.0f,   0.0f, 1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,   1.0f, 0.0f,   0.0f, 1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,   1.0f, 0.0f,   0.0f, 1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,   0.0f, 0.0f,   0.0f, 1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,   0.0f, 1.0f,   0.0f, 1.0f, 0.0f
	};


	//顶点数组vertex array obj
	unsigned int vertex_array_object;
	glGenVertexArrays(1, &vertex_array_object);
	glBindVertexArray(vertex_array_object);

	// 顶点缓存
	unsigned int vertex_buffer_object;
	glGenBuffers(1, &vertex_buffer_object);
	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_object);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//定点layout, 必须在vao之后
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), 0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(5 * sizeof(float)));
	glEnableVertexAttribArray(2);


	Shader object_shader("src/light/multiple_lights/vertex.shader", "src/light/multiple_lights/fragment.shader");
	Shader light_shader("src/light/multiple_lights/vertex.shader", "src/light/multiple_lights/light_fragment.shader");
	// tell stb_image.h to flip loaded texture's on the y-axis.
	stbi_set_flip_vertically_on_load(true);

	//纹理
	unsigned int texture1;
	unsigned int texture2;
	unsigned int texture3;
	{
		glGenTextures(1, &texture1);
		//绑定
		glBindTexture(GL_TEXTURE_2D, texture1);

		// 为当前绑定的纹理对象设置环绕、过滤方式
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		//nrChannels颜色通道个数
		int width, height, nrChannels;
		unsigned char* data = stbi_load("res/image/container2.png", &width, &height, &nrChannels, 0);
		if (data)
		{
			//设置 GL_RED GL_RGB GL_RGBA
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
			//生成mipmap
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else
		{
			std::cout << "Failed to load texture" << std::endl;
		}
		stbi_image_free(data);



		glGenTextures(1, &texture2);
		//绑定
		glBindTexture(GL_TEXTURE_2D, texture2);

		// 为当前绑定的纹理对象设置环绕、过滤方式
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		//nrChannels颜色通道个数
		data = stbi_load("res/image/container2_specular.png", &width, &height, &nrChannels, 0);
		if (data)
		{
			//设置 GL_RED GL_RGB GL_RGBA
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
			//生成mipmap
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else
		{
			std::cout << "Failed to load texture" << std::endl;
		}
		stbi_image_free(data);



		glGenTextures(1, &texture3);
		//绑定
		glBindTexture(GL_TEXTURE_2D, texture3);

		// 为当前绑定的纹理对象设置环绕、过滤方式
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		data = stbi_load("res/image/happy_photo2.jpg", &width, &height, &nrChannels, 0);
		if (data)
		{
			//设置 GL_RED GL_RGB GL_RGBA
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			//生成mipmap
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else
		{
			std::cout << "Failed to load texture" << std::endl;
		}
		stbi_image_free(data);
	}


	glm::mat4 mat = glm::mat4(1.0f);
	glm::mat4 view_matrix;


	glm::mat4 projection_matrix = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);

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



	glm::vec3 cubePositions[] = {
	   glm::vec3(0.0f,  0.0f,  0.0f),
	   glm::vec3(2.0f,  5.0f, -15.0f),
	   glm::vec3(-1.5f, -2.2f, -2.5f),
	   glm::vec3(-3.8f, -2.0f, -12.3f),
	   glm::vec3(2.4f, -0.4f, -3.5f),
	   glm::vec3(-1.7f,  3.0f, -7.5f),
	   glm::vec3(1.3f, -2.0f, -2.5f),
	   glm::vec3(1.5f,  2.0f, -2.5f),
	   glm::vec3(1.5f,  0.2f, -1.5f),
	   glm::vec3(-1.3f,  1.0f, -1.5f)
	};


	// positions of the point lights
	glm::vec3 pointLightPositions[] = {
		glm::vec3(0.7f,  0.2f,  2.0f),
		glm::vec3(2.3f, -3.3f, -4.0f),
		glm::vec3(-4.0f,  2.0f, -12.0f),
		glm::vec3(0.0f,  0.0f, -3.0f)
	};

	while (!glfwWindowShouldClose(window))
	{
		// 计算出delta_time
		current_time = glfwGetTime();
		delta_time = current_time - last_frame_time;
		last_frame_time = current_time;

		// 处理移动
		my_camera.input_callback(window, delta_time);


		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		// glClear(GL_COLOR_BUFFER_BIT);
		// 每次渲染之前清除深度缓冲
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);




		//设置模式
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);


		view_matrix = my_camera.get_look_at_matrix();

		{
			//光源
			light_shader.bind();
			for (int i = 0; i < 4; i++)
			{
				glm::vec3 light_transform = pointLightPositions[i];
				glm::mat4 model_matrix = glm::translate(mat, light_transform);
				model_matrix = glm::rotate(model_matrix, 0.0f, glm::vec3(0.2, 0.4, 0.6));
				model_matrix = glm::scale(model_matrix, glm::vec3(0.5, 0.5, 0.5));
				// mvp矩阵
				light_shader.set_mat4("model_matrix", &model_matrix);
				light_shader.set_mat4("view_matrix", &view_matrix);
				light_shader.set_mat4("projection_matrix", &projection_matrix);

				glBindVertexArray(vertex_array_object);
				glDrawArrays(GL_TRIANGLES, 0, 36);
			}
			glBindVertexArray(0);
		}


		//render
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture1);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture2);
		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, texture3);

		{
			object_shader.bind();

			glm::vec3 camera_pos = my_camera.get_pos();
			object_shader.set_vec3("view_pos", &camera_pos);
			// 设置物体材质
			object_shader.set_int("material.diffuse_color", 0);
			object_shader.set_int("material.mirror_color", 1);
			object_shader.set_int("material.special_color", 2);
			object_shader.set_float("material.shininess", 32.0f);
			// 设置方向光
			object_shader.set_vec3("dir_light.ambient", new glm::vec3(0.01f, 0.01f, 0.01f));
			object_shader.set_vec3("dir_light.diffuse", new glm::vec3(0.4f, 0.4f, 0.4f));
			object_shader.set_vec3("dir_light.specular", new glm::vec3(0.5f, 0.5f, 0.5f));
			object_shader.set_vec3("dir_light.direction", new glm::vec3(-0.2f, -1.0f, -0.3f));
			// 设置点光源
			// point light 0
			glm::vec3 light_transform = pointLightPositions[0];
			object_shader.set_vec3("point_light[0].position", &light_transform);
			object_shader.set_vec3("point_light[0].ambient", new glm::vec3(0.01f, 0.01f, 0.01f));
			object_shader.set_vec3("point_light[0].diffuse", new glm::vec3(0.8f, 0.8f, 0.8f));
			object_shader.set_vec3("point_light[0].specular", new glm::vec3(1.0f, 1.0f, 1.0f));
			object_shader.set_float("point_light[0].constant", 1.0f);
			object_shader.set_float("point_light[0].linear", 0.09f);
			object_shader.set_float("point_light[0].quadratic", 0.032f);
			// point light 1
			light_transform = pointLightPositions[1];
			object_shader.set_vec3("point_light[1].position", &light_transform);
			object_shader.set_vec3("point_light[1].ambient", new glm::vec3(0.01f, 0.01f, 0.01f));
			object_shader.set_vec3("point_light[1].diffuse", new glm::vec3(0.8f, 0.8f, 0.8f));
			object_shader.set_vec3("point_light[1].specular", new glm::vec3(1.0f, 1.0f, 1.0f));
			object_shader.set_float("point_light[1].constant", 1.0f);
			object_shader.set_float("point_light[1].linear", 0.09f);
			object_shader.set_float("point_light[1].quadratic", 0.032f);
			// point light 2
			light_transform = pointLightPositions[2];
			object_shader.set_vec3("point_light[2].position", &light_transform);
			object_shader.set_vec3("point_light[2].ambient", new glm::vec3(0.01f, 0.01f, 0.01f));
			object_shader.set_vec3("point_light[2].diffuse", new glm::vec3(0.8f, 0.8f, 0.8f));
			object_shader.set_vec3("point_light[2].specular", new glm::vec3(1.0f, 1.0f, 1.0f));
			object_shader.set_float("point_light[2].constant", 1.0f);
			object_shader.set_float("point_light[2].linear", 0.09f);
			object_shader.set_float("point_light[2].quadratic", 0.032f);
			// point light 3
			light_transform = pointLightPositions[3];
			object_shader.set_vec3("point_light[3].position", &light_transform);
			object_shader.set_vec3("point_light[3].ambient", new glm::vec3(0.01f, 0.01f, 0.01f));
			object_shader.set_vec3("point_light[3].diffuse", new glm::vec3(0.8f, 0.8f, 0.8f));
			object_shader.set_vec3("point_light[3].specular", new glm::vec3(1.0f, 1.0f, 1.0f));
			object_shader.set_float("point_light[3].constant", 1.0f);
			object_shader.set_float("point_light[3].linear", 0.09f);
			object_shader.set_float("point_light[3].quadratic", 0.032f);

			// 手电筒
			glm::vec3 camera_dir = my_camera.get_dir();
			object_shader.set_vec3("flash_light.position", &camera_pos);
			object_shader.set_vec3("flash_light.direction", &camera_dir);
			object_shader.set_float("flash_light.cutOff", glm::cos(glm::radians(12.5f)));
			object_shader.set_float("flash_light.outCutOff", glm::cos(glm::radians(18.5f)));

			for (unsigned int i = 0; i < 10; i++)
			{
				//物体
				glm::mat4 model_matrix = glm::translate(mat, cubePositions[i]);
				model_matrix = glm::rotate(model_matrix, glm::radians(20.0f * i), glm::vec3(1.0f, 0.3f, 0.5f));
				model_matrix = glm::scale(model_matrix, glm::vec3(1, 1, 1));
				// mvp矩阵
				object_shader.set_mat4("model_matrix", &model_matrix);
				object_shader.set_mat4("view_matrix", &view_matrix);
				object_shader.set_mat4("projection_matrix", &projection_matrix);
				glBindVertexArray(vertex_array_object);
				glDrawArrays(GL_TRIANGLES, 0, 36);
			}

			glBindVertexArray(0);
		}

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}
