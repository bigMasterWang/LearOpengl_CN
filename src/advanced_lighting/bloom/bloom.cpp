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
#include "bloom.h"

int Bloom::run()
{
	// settings
	const unsigned int SCR_WIDTH = 800;
	const unsigned int SCR_HEIGHT = 600;
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	// 开启抗锯齿
	glfwWindowHint(GLFW_SAMPLES, 16);

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

	float cubeVertices[] = {
		// positions            // normals         // texcoords
		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f,	   0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f,	   1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f, 0.0f, 0.0f, -1.0f,	   1.0f, 1.0f,
		 0.5f,  0.5f, -0.5f, 0.0f, 0.0f, -1.0f,	   1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f, 0.0f, 0.0f, -1.0f,	   0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f,	   0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 1.0f,	   0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 1.0f,	   1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 1.0f,	   1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 1.0f,	   1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 1.0f,	   0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 1.0f,	   0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f, -1.0f, 0.0f, 0.0f,	   1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f, -1.0f, 0.0f, 0.0f,	   1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f,	   0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f,	   0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f, -1.0f, 0.0f, 0.0f,	   0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f, -1.0f, 0.0f, 0.0f,	   1.0f, 0.0f,

		 0.5f,  0.5f,  0.5f, 1.0f, 0.0f, 0.0f,	   1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f, 1.0f, 0.0f, 0.0f,	   1.0f, 1.0f,
		 0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,	   0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,	   0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f, 1.0f, 0.0f, 0.0f,	   0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f, 1.0f, 0.0f, 0.0f,	   1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f,	   0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f,	   1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f, 0.0f, -1.0f, 0.0f,	   1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f, 0.0f, -1.0f, 0.0f,	   1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f, 0.0f, -1.0f, 0.0f,	   0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f,	   0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f, 0.0f, 1.0f, 0.0f,	   0.0f, 1.0f,
		 0.5f,  0.5f, -0.5f, 0.0f, 1.0f, 0.0f,	   1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f, 0.0f, 1.0f, 0.0f,	   1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f, 0.0f, 1.0f, 0.0f,	   1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f, 0.0f, 1.0f, 0.0f,	   0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f, 0.0f, 1.0f, 0.0f,	   0.0f, 1.0f,
	};

	unsigned int box_vao, box_vbo;
	glGenVertexArrays(1, &box_vao);
	glBindVertexArray(box_vao);

	glGenBuffers(1, &box_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, box_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), &cubeVertices, GL_STATIC_DRAW);


	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);


	glm::vec3 translations[] = {
		glm::vec3(0.0f,1.5f, -1.0f),
		glm::vec3(1.0f,0.0f, 0.0f),
		glm::vec3(3.0f,0.0f, 0.0f),
	};


	float planeVertices[] = {
		// positions   // texCoords
		-1.0f,  1.0f, 0.0f,  0.0f, 1.0f,
		-1.0f, -1.0f, 0.0f,  0.0f, 0.0f,
		 1.0f, -1.0f, 0.0f,  1.0f, 0.0f,
		-1.0f,  1.0f, 0.0f,  0.0f, 1.0f,
		 1.0f, -1.0f, 0.0f,  1.0f, 0.0f,
		 1.0f,  1.0f, 0.0f,  1.0f, 1.0f
	};

	unsigned int vao, vbo;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(planeVertices), &planeVertices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));


	Shader depth_shader("src/advanced_lighting/bloom/dp_vs.shader", "src/advanced_lighting/bloom/dp_fs.shader");
	Shader scene_shader("src/advanced_lighting/bloom/vs.shader", "src/advanced_lighting/bloom/fs.shader");
	Shader light_shader("src/advanced_lighting/bloom/light_vs.shader", "src/advanced_lighting/bloom/light_fs.shader");
	Shader blur_shader("src/advanced_lighting/bloom/blur_vs.shader", "src/advanced_lighting/bloom/blur_fs.shader");

	unsigned int floor_texture = create_texture("E:/VSProjects/LearnOpengl_CN/res/image/wood.png");
	unsigned int box_texture = create_texture("E:/VSProjects/LearnOpengl_CN/res/image/happy_photo2.jpg");



	// 浮点帧缓冲
	unsigned int fbo;
	glGenFramebuffers(1, &fbo);
	// 创建好纹理后, 将他附加到帧缓冲上
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);

	// 帧缓冲
	unsigned int frame_textures[2];
	glGenTextures(2, frame_textures);
	for (unsigned int i = 0; i < 2; i++)
	{

		glBindTexture(GL_TEXTURE_2D, frame_textures[i]);
		// HDR缓冲
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, SCR_WIDTH, SCR_HEIGHT, 0, GL_RGBA, GL_FLOAT, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		// 确定是第几个附件
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, frame_textures[i], 0);
		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
			std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
	}

	// 渲染缓冲对象附加(RenderBuffer object)
	// 绑定到渲染缓冲对象， 主要是为了有深度检测
	unsigned int rbo;
	glGenRenderbuffers(1, &rbo);
	glBindRenderbuffer(GL_RENDERBUFFER, rbo);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, SCR_WIDTH, SCR_HEIGHT);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, rbo);

	// 显式地告诉opengl， 一个帧缓冲，有两个颜色缓冲附件
	GLuint attachments[2] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1 };
	glDrawBuffers(2, attachments);

	//blur的帧缓冲
	unsigned int blur_fbo[2];
	glGenFramebuffers(2, blur_fbo);
	unsigned int blur_textures[2];
	glGenTextures(2, blur_textures);
	for (unsigned int i = 0; i < 2; i++)
	{
		glBindFramebuffer(GL_FRAMEBUFFER, blur_fbo[i]);
		glBindTexture(GL_TEXTURE_2D, blur_textures[i]);
		// HDR缓冲
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, SCR_WIDTH, SCR_HEIGHT, 0, GL_RGBA, GL_FLOAT, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		// 确定是第几个附件, tmd这里每一个都是帧缓冲的第一个附件， wrtnn
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, blur_textures[i], 0);
		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
			std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
	}


	// 算出 delta_time
	float last_frame_time = 0.0f;
	float delta_time = 0.0f;
	float current_time = 0.0f;
	// 隐藏鼠标
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	// 鼠标输入
	extern Camera my_camera;
	glfwSetCursorPosCallback(window, global_mouse_callback);

	glm::mat4 projection_matrix = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.01f, 1000.0f);



	GLfloat near_plane = 1.0f, far_plane = 7.5f;
	glm::mat4 lightProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, near_plane, far_plane);


	// 六個箱子
	glm::vec3 box_translations[] = {
		glm::vec3(0.0, 0.0, 2.0),
		glm::vec3(2.0, 0.0, 0.0),
		glm::vec3(-2.0, 0.0, 0.0),
		glm::vec3(0.0, 2.0, 0.0),
		glm::vec3(0.0, -2.0, 0.0),
		glm::vec3(0.0, 0.0, -2.0)
	};
	glm::vec3 box_rotations[] = {
		glm::vec3(0.0, 0.0, 1.0),
		glm::vec3(1.0, 0.0, 0.0),
		glm::vec3(-1.0, 0.0, 0.0),
		glm::vec3(0.0, 1.0, 0.0),
		glm::vec3(0.0, -1.0, 0.0),
		glm::vec3(0.0, 0.0, -1.0)
	};

	//四个灯光
	glm::vec3 light_positions[] = {
		glm::vec3(2.0, 2.0, 2.0),
		glm::vec3(2.0, 2.0, -2.0),
		glm::vec3(-2.0, 2.0, 2.0),
		glm::vec3(-2.0, 2.0, -2.0)
	};
	//四个灯光的颜色
	glm::vec3 light_colors[] = {
		glm::vec3(10.0, 10.0, 10.0),
		glm::vec3(0.0, 0.0, 10.0),
		glm::vec3(10.0, 0.0, 0.0),
		glm::vec3(0.0, 10.0, 0.0)
	};

	bool use_blur = true;

	while (!glfwWindowShouldClose(window))
	{
		current_time = glfwGetTime();
		delta_time = current_time - last_frame_time;
		last_frame_time = current_time;
		my_camera.input_callback(window, delta_time);

		// 1. 绑定帧缓冲
		glBindFramebuffer(GL_FRAMEBUFFER, fbo);

		glEnable(GL_DEPTH_TEST);
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		glm::mat4 view_matrix = my_camera.get_look_at_matrix();
		glm::vec3 view_pos = my_camera.get_pos();
		glm::mat4 mat = glm::mat4(1.0f);
		{

			//渲染四个灯泡， 我日他奶奶
			light_shader.bind();
			light_shader.set_mat4("projection", &projection_matrix);
			light_shader.set_mat4("view", &view_matrix);
			for (int i = 0; i < 4; i++)
			{
				glm::mat4 _m = glm::translate(mat, light_positions[i]);
				_m = glm::rotate(_m, 45.0f, box_rotations[i]);
				_m = glm::scale(_m, glm::vec3(0.2, 0.2, 0.2));
				light_shader.set_mat4("model", &_m);
				light_shader.set_vec3("light_color", &light_colors[i]);
				glBindVertexArray(box_vao);
				glDrawArrays(GL_TRIANGLES, 0, 36);
			}


			depth_shader.bind();
			for (GLuint i = 0; i < 4; i++)
			{
				depth_shader.set_vec3(("light_colors[" + std::to_string(i) + "]").c_str(), &light_colors[i]);
				depth_shader.set_vec3(("light_pos[" + std::to_string(i) + "]").c_str(), &light_positions[i]);
			}
			depth_shader.set_vec3("view_pos", &view_pos);
			depth_shader.set_mat4("projection", &projection_matrix);
			depth_shader.set_mat4("view", &view_matrix);


			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, floor_texture);
			depth_shader.set_int("frame_texture", 0);
			// 这个地方要渲染6个箱子
			// 6个箱子有不同的平移和旋转
			for (int i = 0; i < 6; i++)
			{
				glm::mat4 _m = glm::translate(mat, box_translations[i]);
				_m = glm::rotate(_m, 45.0f, box_rotations[i]);
				depth_shader.set_mat4("model", &_m);
				glBindVertexArray(box_vao);
				glDrawArrays(GL_TRIANGLES, 0, 36);
			}

			glBindVertexArray(0);
			// 到此，就算是把贴图渲染在了帧缓冲的贴图上
		}


		//{
		//	// 清空帧缓冲
		//	glBindFramebuffer(GL_FRAMEBUFFER, 0);
		//	// 清空一下渲染
		//	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//	glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
		//}


		{
			//blur流程
			glBindFramebuffer(GL_FRAMEBUFFER, blur_fbo[0]);
			blur_shader.bind();
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, frame_textures[1]);
			blur_shader.set_int("blur_texture", 0);
			blur_shader.set_int("horizontal", 0);
			glBindVertexArray(vao);
			glDrawArrays(GL_TRIANGLES, 0, 6);


			//blur流程
			glBindFramebuffer(GL_FRAMEBUFFER, blur_fbo[1]);
			blur_shader.bind();
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, blur_textures[0]);
			blur_shader.set_int("blur_texture", 0);
			blur_shader.set_int("horizontal", 1);
			glBindVertexArray(vao);
			glDrawArrays(GL_TRIANGLES, 0, 6);
		}

		{
			// 清空帧缓冲
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
			// 清空一下渲染
			glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
		}


		{
			scene_shader.bind();
			scene_shader.set_int("use_blur", use_blur);
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, frame_textures[0]);
			scene_shader.set_int("frame_texture", 0);
			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, blur_textures[1]);
			scene_shader.set_int("blur_texture", 1);
			glBindVertexArray(vao);
			glDrawArrays(GL_TRIANGLES, 0, 6);
		}

		if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS)
		{
			use_blur = !use_blur;
		}
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}
