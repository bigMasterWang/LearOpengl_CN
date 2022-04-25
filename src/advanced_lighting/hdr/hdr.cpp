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
#include "hdr.h"


// low dynamic range
int Hdr::run()

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


	Shader depth_shader("src/advanced_lighting/hdr/dp_vs.shader", "src/advanced_lighting/hdr/dp_fs.shader");
	Shader scene_shader("src/advanced_lighting/hdr/vs.shader", "src/advanced_lighting/hdr/fs.shader");


	unsigned int floor_texture = create_texture("E:/VSProjects/LearnOpengl_CN/res/image/wood.png");
	unsigned int box_texture = create_texture("E:/VSProjects/LearnOpengl_CN/res/image/happy_photo2.jpg");

	// 浮点帧缓冲
	unsigned int fbo;
	glGenFramebuffers(1, &fbo);

	// 帧缓冲
	unsigned int frame_texture;
	{
		glGenTextures(1, &frame_texture);
		glBindTexture(GL_TEXTURE_2D, frame_texture);
		// HDR缓冲
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, SCR_WIDTH, SCR_HEIGHT, 0, GL_RGBA, GL_FLOAT, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);



		// 渲染缓冲对象附加(RenderBuffer object)
		unsigned int rbo;
		glGenRenderbuffers(1, &rbo);
		glBindRenderbuffer(GL_RENDERBUFFER, rbo);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, SCR_WIDTH, SCR_HEIGHT);

		// 创建好纹理后, 将他附加到帧缓冲上
		glBindFramebuffer(GL_FRAMEBUFFER, fbo);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, frame_texture, 0);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, rbo);

		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
			std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
		//绑定到默认的帧缓冲
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}


	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);



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



	glm::vec3 light_colors[] = {
		glm::vec3(200.0f, 200.0f, 200.0f),
		glm::vec3(0.1f, 0.0f, 0.0f),
		glm::vec3(0.0f, 0.0f, 0.2f),
		glm::vec3(0.0f, 0.1f, 0.0f)
	};
	glm::vec3 light_pos[] = {
		glm::vec3(0.0f, 0.0f, 49.5f),
		glm::vec3(-1.4f, -1.9f, 9.0f),
		glm::vec3(0.0f, -1.8f, 4.0f),
		glm::vec3(0.8f, -1.7f, 6.0f)
	};
	int use_hdr = 1;
	while (!glfwWindowShouldClose(window))
	{
		if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS)
		{
			use_hdr += 1;
			use_hdr = use_hdr % 3;
		}
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

			depth_shader.bind();
			for (GLuint i = 0; i < 4; i++)
			{
				depth_shader.set_vec3(("light_colors[" + std::to_string(i) + "]").c_str(), &light_colors[i]);
				depth_shader.set_vec3(("light_pos[" + std::to_string(i) + "]").c_str(), &light_pos[i]);
			}
			depth_shader.set_int("use_hdr", use_hdr);
			depth_shader.set_vec3("view_pos", &view_pos);
			depth_shader.set_mat4("projection", &projection_matrix);
			depth_shader.set_mat4("view", &view_matrix);
			mat = glm::scale(mat, glm::vec3(1.0, 1.0, 10.0));
			depth_shader.set_mat4("model", &mat);


			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, floor_texture);
			depth_shader.set_int("frame_texture", 0);
			glBindVertexArray(box_vao);
			glDrawArrays(GL_TRIANGLES, 0, 36);
			glBindVertexArray(0);
			// 到此，就算是把贴图渲染在了帧缓冲的贴图上
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
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, frame_texture);
			scene_shader.set_int("frame_texture", 0);
			glBindVertexArray(vao);
			glDrawArrays(GL_TRIANGLES, 0, 6);
		}


		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}
