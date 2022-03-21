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
#include"load_model/Model.h"
#include"blinn_phone.h"

int BlinnPhone::run()

{
	// settings
	const unsigned int SCR_WIDTH = 800;
	const unsigned int SCR_HEIGHT = 600;
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	// ¿ªÆô¿¹¾â³Ý
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



	//float cubeVertices[] = {
	//	// pos, texture, nor
	//	-0.5f, -0.5f, -0.5f,
	//	 0.5f, -0.5f, -0.5f,
	//	 0.5f,  0.5f, -0.5f,
	//	 0.5f,  0.5f, -0.5f,
	//	-0.5f,  0.5f, -0.5f,
	//	-0.5f, -0.5f, -0.5f,

	//	-0.5f, -0.5f,  0.5f,
	//	 0.5f, -0.5f,  0.5f,
	//	 0.5f,  0.5f,  0.5f,
	//	 0.5f,  0.5f,  0.5f,
	//	-0.5f,  0.5f,  0.5f,
	//	-0.5f, -0.5f,  0.5f,

	//	-0.5f,  0.5f,  0.5f,
	//	-0.5f,  0.5f, -0.5f,
	//	-0.5f, -0.5f, -0.5f,
	//	-0.5f, -0.5f, -0.5f,
	//	-0.5f, -0.5f,  0.5f,
	//	-0.5f,  0.5f,  0.5f,

	//	 0.5f,  0.5f,  0.5f,
	//	 0.5f,  0.5f, -0.5f,
	//	 0.5f, -0.5f, -0.5f,
	//	 0.5f, -0.5f, -0.5f,
	//	 0.5f, -0.5f,  0.5f,
	//	 0.5f,  0.5f,  0.5f,

	//	-0.5f, -0.5f, -0.5f,
	//	 0.5f, -0.5f, -0.5f,
	//	 0.5f, -0.5f,  0.5f,
	//	 0.5f, -0.5f,  0.5f,
	//	-0.5f, -0.5f,  0.5f,
	//	-0.5f, -0.5f, -0.5f,

	//	-0.5f,  0.5f, -0.5f,
	//	 0.5f,  0.5f, -0.5f,
	//	 0.5f,  0.5f,  0.5f,
	//	 0.5f,  0.5f,  0.5f,
	//	-0.5f,  0.5f,  0.5f,
	//	-0.5f,  0.5f, -0.5f
	//};

	//unsigned int vao, vbo;
	//glGenVertexArrays(1, &vao);
	//glBindVertexArray(vao);

	//glGenBuffers(1, &vbo);
	//glBindBuffer(GL_ARRAY_BUFFER, vbo);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), &cubeVertices, GL_STATIC_DRAW);


	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	//glEnableVertexAttribArray(0);



	float planeVertices[] = {
		// positions            // normals         // texcoords
		 10.0f, -0.5f,  10.0f,  0.0f, 1.0f, 0.0f,  10.0f,  0.0f,
		-10.0f, -0.5f,  10.0f,  0.0f, 1.0f, 0.0f,   0.0f,  0.0f,
		-10.0f, -0.5f, -10.0f,  0.0f, 1.0f, 0.0f,   0.0f, 10.0f,

		 10.0f, -0.5f,  10.0f,  0.0f, 1.0f, 0.0f,  10.0f,  0.0f,
		-10.0f, -0.5f, -10.0f,  0.0f, 1.0f, 0.0f,   0.0f, 10.0f,
		 10.0f, -0.5f, -10.0f,  0.0f, 1.0f, 0.0f,  10.0f, 10.0f
	};

	unsigned int vao, vbo;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(planeVertices), &planeVertices, GL_STATIC_DRAW);


	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	Shader scene_shader("src/advanced_lighting/blinn_phone/vs.shader", "src/advanced_lighting/blinn_phone/fs.shader");


	unsigned int floor_texture;
	glGenTextures(1, &floor_texture);

	int width, height, nrComponents;
	unsigned char* data = stbi_load("res/image/happy_photo.jpg", &width, &height, &nrComponents, 0);
	if (data)
	{
		GLenum format;
		if (nrComponents == 1)
			format = GL_RED;
		else if (nrComponents == 3)
			format = GL_RGB;
		else if (nrComponents == 4)
			format = GL_RGBA;

		glBindTexture(GL_TEXTURE_2D, floor_texture);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, format == GL_RGBA ? GL_CLAMP_TO_EDGE : GL_REPEAT); // for this tutorial: use GL_CLAMP_TO_EDGE to prevent semi-transparent borders. Due to interpolation it takes texels from next repeat 
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, format == GL_RGBA ? GL_CLAMP_TO_EDGE : GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_image_free(data);
	}
	else
	{
		std::cout << "Texture failed to load at path" << std::endl;
		stbi_image_free(data);
	}



	// Ëã³ö delta_time
	float last_frame_time = 0.0f;
	float delta_time = 0.0f;
	float current_time = 0.0f;
	// Òþ²ØÊó±ê
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	// Êó±êÊäÈë
	extern Camera my_camera;
	glfwSetCursorPosCallback(window, global_mouse_callback);

	glm::mat4 projection_matrix = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.01f, 1000.0f);

	// ¿ªÆôÉî¶È²âÊÔ
	glEnable(GL_DEPTH_TEST);
	// ¿ªÆô¿¹¾â³Ý
	glEnable(GL_MULTISAMPLE);


	glm::vec3 light_pos3 = glm::vec3(0.0, 0.0, 0.0);
	bool use_phone = false;

	//glEnable(GL_FRAMEBUFFER_SRGB);

	while (!glfwWindowShouldClose(window))
	{
		//GLenum errCode;
		//const GLubyte* errString;
		//while ((errCode = glGetError()) != GL_NO_ERROR)
		//{
		//	errString = glGetString(errCode);
		//	fprintf(stderr, "OpenGL error:%s \n", errString);
		//}

		current_time = glfwGetTime();
		delta_time = current_time - last_frame_time;
		last_frame_time = current_time;
		my_camera.input_callback(window, delta_time);
		if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS)
		{
			use_phone = !use_phone;
		}

		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		scene_shader.bind();
		scene_shader.set_mat4("projection", &projection_matrix);
		glm::mat4 view_matrix = my_camera.get_look_at_matrix();
		scene_shader.set_mat4("view", &view_matrix);


		glm::mat4 mat = glm::mat4(1.0f);
		scene_shader.set_mat4("model", &mat);


		glm::vec3 view_pos = my_camera.get_pos();
		scene_shader.set_vec3("view_pos", &view_pos);
		scene_shader.set_vec3("light_pos", &light_pos3);

		scene_shader.set_int("use_phone", use_phone);

		glBindVertexArray(vao);

		scene_shader.set_int("floorTexture", 0);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, floor_texture);

		glDrawArrays(GL_TRIANGLES, 0, 6);
		glBindVertexArray(0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}