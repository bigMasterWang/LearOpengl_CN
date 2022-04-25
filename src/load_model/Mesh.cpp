#include"glad/glad.h"
#include "Mesh.h"
#include"glfw3.h"
#include <vector>



void Mesh::set_up_mesh()
{
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);


	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);


	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

	assert(vertices.size() == indices.size());
	// …Ë÷√layout
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, tex_coords));
	glEnableVertexAttribArray(2);

}



Mesh::Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures) :vertices(vertices),
indices(indices), textures(textures)
{
	set_up_mesh();
}

void Mesh::draw(Shader shader)
{
	shader.bind();
	unsigned int diffuseNr = 1;
	unsigned int specularNr = 1;
	for (unsigned int i = 0; i < textures.size(); i++)
	{
		glActiveTexture(GL_TEXTURE0 + i);
		string number;
		string name = textures[i].type;
		if (name == "texture_diffuse")
			number = std::to_string(diffuseNr++);
		if (name == "texture_specular")
			number = std::to_string(specularNr++);
		shader.set_int((name + number).c_str(), i);
		// texture_diffuse1
		glBindTexture(GL_TEXTURE_2D, textures[i].id);
	}

	//ªÊ÷∆Õ¯∏Ò
	glBindVertexArray(VAO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}
