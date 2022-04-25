
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
#include"DefferedShading.h"

int DefferedShading::run()

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


	Shader depth_shader("src/advanced_lighting/deffered_shading/dp_vs.shader", "src/advanced_lighting/deffered_shading/dp_fs.shader");
	Shader scene_shader("src/advanced_lighting/deffered_shading/vs.shader", "src/advanced_lighting/deffered_shading/fs.shader");
	Shader light_shader("src/advanced_lighting/deffered_shading/light_vs.shader", "src/advanced_lighting/deffered_shading/light_fs.shader");

	unsigned int floor_texture = create_texture("E:/VSProjects/LearnOpengl_CN/res/image/wood.png");
	unsigned int box_texture = create_texture("E:/VSProjects/LearnOpengl_CN/res/image/happy_photo2.jpg");

	// 浮点帧缓冲
	unsigned int fbo;
	glGenFramebuffers(1, &fbo);
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);

	// 渲染缓冲对象附加(RenderBuffer object)
	unsigned int rbo;
	glGenRenderbuffers(1, &rbo);
	glBindRenderbuffer(GL_RENDERBUFFER, rbo);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, SCR_WIDTH, SCR_HEIGHT);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, rbo);

	// 颜色缓冲
	unsigned int frame_texture;
	glGenTextures(1, &frame_texture);
	glBindTexture(GL_TEXTURE_2D, frame_texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, SCR_WIDTH, SCR_HEIGHT, 0, GL_RGB, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// 创建好纹理后, 将他附加到帧缓冲上
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, frame_texture, 0);
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;

	// 法线缓冲
	unsigned int normal_texture;
	glGenTextures(1, &normal_texture);
	glBindTexture(GL_TEXTURE_2D, normal_texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, SCR_WIDTH, SCR_HEIGHT, 0, GL_RGB, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, normal_texture, 0);

	//位置
	unsigned int position_specular_texture;
	glGenTextures(1, &position_specular_texture);
	glBindTexture(GL_TEXTURE_2D, position_specular_texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, SCR_WIDTH, SCR_HEIGHT, 0, GL_RGB, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT2, GL_TEXTURE_2D, position_specular_texture, 0);


	// 三个附件
	GLuint attachments[3] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2 };
	glDrawBuffers(3, attachments);


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


	int light_number = 32;
	std::vector<glm::vec3> light_colors;
	std::vector<glm::vec3> light_pos;

	//x， z， 0 ~ 10， y： 1~4
	std::srand(13);
	for (unsigned int i = 0; i < light_number; i++)
	{
		float x = static_cast<float>((std::rand() % 100) / 10.0 - 5.0);
		float y = static_cast<float>((std::rand() % 6) - 2.0);
		float z = static_cast<float>((std::rand() % 100) / 10.0 - 10.0);
		light_pos.push_back(glm::vec3(x, y, z));


		float r = static_cast<float>((std::rand() % 100) / 200.0f + 0.5f);
		float g = static_cast<float>((std::rand() % 100) / 200.0f + 0.5f);
		float b = static_cast<float>((std::rand() % 100) / 200.0f + 0.5f);
		light_colors.push_back(glm::vec3(r, g, b));
	}


	int use_hdr = 1;

	Model ourModel("res/objects/nanosuit.obj");

	glm::vec3 model_position[] = {
		glm::vec3(0.0, 0.0, 0.0),
		glm::vec3(10.0, 0.0, 0.0),
		glm::vec3(20.0, 0.0, 0.0),
		glm::vec3(30.0, 0.0, 0.0),
		glm::vec3(40.0, 0.0, 0.0),
		glm::vec3(-10.0, 0.0, 0.0),
		glm::vec3(-20.0, 0.0, 0.0),
		glm::vec3(-30.0, 0.0, 0.0),
		glm::vec3(-40.0, 0.0, 0.0),
		glm::vec3(-50.0, 0.0, 0.0),
	};



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
			depth_shader.set_mat4("projection", &projection_matrix);
			depth_shader.set_mat4("view", &view_matrix);


			glm::mat4 scale_mat = glm::scale(mat, glm::vec3(0.1, 0.1, 0.1));
			for (int p = 0; p < 10; p++)
			{
				for (int i = 0; i < 10; i++)
				{
					glm::mat4 model_mat = glm::translate(scale_mat, model_position[i] + glm::vec3(0.0, 0.0, -10.0 * p));
					depth_shader.set_mat4("model", &model_mat);
					ourModel.draw(depth_shader);
				}
			}

			// 灯的位置没问题， 有问题的是模型的位置
			glm::mat4 model_mat = glm::scale(mat, glm::vec3(0.1, 0.1, 0.1));
			depth_shader.set_mat4("model", &model_mat);
			ourModel.draw(depth_shader);

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
			scene_shader.set_int("light_number", light_number);
			for (GLuint i = 0; i < light_number; i++)
			{
				scene_shader.set_vec3(("light_colors[" + std::to_string(i) + "]").c_str(), &light_colors[i]);
				scene_shader.set_vec3(("light_pos[" + std::to_string(i) + "]").c_str(), &light_pos[i]);
			}
			scene_shader.set_vec3("view_pos", &view_pos);
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, frame_texture);
			scene_shader.set_int("frame_texture", 0);
			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, normal_texture);
			scene_shader.set_int("normal_texture", 1);
			glActiveTexture(GL_TEXTURE2);
			glBindTexture(GL_TEXTURE_2D, position_specular_texture);
			scene_shader.set_int("position_specular_texture", 2);
			glBindVertexArray(vao);
			glDrawArrays(GL_TRIANGLES, 0, 6);
		}



		//// 复用颜色缓冲
		glBindFramebuffer(GL_READ_FRAMEBUFFER, fbo);
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
		glBlitFramebuffer(0, 0, SCR_WIDTH, SCR_HEIGHT, 0, 0, SCR_WIDTH, SCR_HEIGHT, GL_DEPTH_BUFFER_BIT, GL_NEAREST);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);

		{
			// 渲染光源
			light_shader.bind();
			light_shader.set_mat4("projection", &projection_matrix);
			light_shader.set_mat4("view", &view_matrix);
			for (unsigned int i = 0; i < light_number; i++)
			{
				glm::mat4 model_mat = glm::translate(mat, light_pos[i]);
				model_mat = glm::scale(model_mat, glm::vec3(0.1, 0.1, 0.1));
				light_shader.set_mat4("model", &model_mat);
				light_shader.set_vec3("light_color", &light_colors[i]);
				glBindVertexArray(box_vao);
				glDrawArrays(GL_TRIANGLES, 0, 36);
			}
		}


		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}
