#include"CastLight.h"
#include<glad/glad.h>
#include<glfw3.h>
#include<iostream>
#include"tools/shader.h"
#include"tools/stb_image.h"
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include"tools/Camera.h"


int CastLight::run()
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


	//????????vertex array obj
	unsigned int vertex_array_object;
	glGenVertexArrays(1, &vertex_array_object);
	glBindVertexArray(vertex_array_object);

	// ????????
	unsigned int vertex_buffer_object;
	glGenBuffers(1, &vertex_buffer_object);
	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_object);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//????layout, ??????vao????
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), 0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(5 * sizeof(float)));
	glEnableVertexAttribArray(2);


	Shader object_shader("src/light/cast_light/vertex.shader", "src/light/cast_light/fragment.shader");
	Shader light_shader("src/light/cast_light/vertex.shader", "src/light/cast_light/light_fragment.shader");
	// tell stb_image.h to flip loaded texture's on the y-axis.
	stbi_set_flip_vertically_on_load(true);

	//????
	unsigned int texture1;
	unsigned int texture2;
	{
		glGenTextures(1, &texture1);
		//????
		glBindTexture(GL_TEXTURE_2D, texture1);

		// ??????????????????????????????????????
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		//nrChannels????????????
		int width, height, nrChannels;
		unsigned char* data = stbi_load("res/image/container2.png", &width, &height, &nrChannels, 0);
		if (data)
		{
			//???? GL_RED GL_RGB GL_RGBA
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
			//????mipmap
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else
		{
			std::cout << "Failed to load texture" << std::endl;
		}
		stbi_image_free(data);



		glGenTextures(1, &texture2);
		//????
		glBindTexture(GL_TEXTURE_2D, texture2);

		// ??????????????????????????????????????
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		//nrChannels????????????
		data = stbi_load("res/image/container2_specular.png", &width, &height, &nrChannels, 0);
		if (data)
		{
			//???? GL_RED GL_RGB GL_RGBA
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
			//????mipmap
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

	// ????????????
	glEnable(GL_DEPTH_TEST);


	// ???? delta_time
	float last_frame_time = 0.0f;
	float delta_time = 0.0f;
	float current_time = 0.0f;


	// ????????
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// ????????
	extern Camera my_camera;
	glfwSetCursorPosCallback(window, global_mouse_callback);



	glm::vec3 object_transform(0.0f, 0.0f, -2.0f);
	glm::vec3 light_transform(2.0f, 2.5f, -5.0f);



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


	while (!glfwWindowShouldClose(window))
	{
		// ??????delta_time
		current_time = glfwGetTime();
		delta_time = current_time - last_frame_time;
		last_frame_time = current_time;

		// ????????
		my_camera.input_callback(window, delta_time);


		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		// glClear(GL_COLOR_BUFFER_BIT);
		// ????????????????????????
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);




		//????????
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);


		view_matrix = my_camera.get_look_at_matrix();

		{
			//????
			light_shader.bind();
			glm::mat4 model_matrix = glm::translate(mat, light_transform);
			model_matrix = glm::rotate(model_matrix, 0.0f, glm::vec3(0.2, 0.4, 0.6));
			model_matrix = glm::scale(model_matrix, glm::vec3(0.5, 0.5, 0.5));
			// mvp????
			light_shader.set_mat4("model_matrix", &model_matrix);
			light_shader.set_mat4("view_matrix", &view_matrix);
			light_shader.set_mat4("projection_matrix", &projection_matrix);

			glBindVertexArray(vertex_array_object);
			//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
			glDrawArrays(GL_TRIANGLES, 0, 36);
			glBindVertexArray(0);
		}


		//render
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture1);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture2);

		{
			object_shader.bind();
			// ????????
			object_shader.set_int("light_form", 3);


			glm::vec3 camera_pos = my_camera.get_pos();
			object_shader.set_vec3("view_pos", &camera_pos);
			// ????????????
			object_shader.set_int("material.diffuse_color", 0);
			object_shader.set_int("material.mirror_color", 1);
			object_shader.set_float("material.shininess", 32.0f);
			// ????????
			object_shader.set_vec3("light.environment_color", new glm::vec3(0.2f, 0.2f, 0.2f));
			object_shader.set_vec3("light.diffuse_color", new glm::vec3(0.5f, 0.5f, 0.5f));
			object_shader.set_vec3("light.mirror_color", new glm::vec3(1.0f, 1.0f, 1.0f));
			object_shader.set_vec3("light.direction", new glm::vec3(-0.2f, -1.0f, -0.3f));
			object_shader.set_vec3("light.position", &light_transform);
			object_shader.set_float("light.constant", 1.0f);
			object_shader.set_float("light.linear", 0.09f);
			object_shader.set_float("light.quadratic", 0.032f);


			glm::vec3 camera_dir = my_camera.get_dir();
			object_shader.set_vec3("flash_light.position", &camera_pos);
			object_shader.set_vec3("flash_light.direction", &camera_dir);
			object_shader.set_float("flash_light.cutOff", glm::cos(glm::radians(12.5f)));
			object_shader.set_float("flash_light.outCutOff", glm::cos(glm::radians(18.5f)));

			for (unsigned int i = 0; i < 10; i++)
			{
				//????
				glm::mat4 model_matrix = glm::translate(mat, cubePositions[i]);
				model_matrix = glm::rotate(model_matrix, glm::radians(20.0f * i), glm::vec3(1.0f, 0.3f, 0.5f));
				model_matrix = glm::scale(model_matrix, glm::vec3(1, 1, 1));
				// mvp????
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
