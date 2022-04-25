#pragma once
#include<glm.hpp>
#include <string>
#include <vector>
#include<tools/shader.h>
#include <assimp\types.h>
using namespace std;


struct Vertex
{
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 tex_coords;
};


struct Texture
{
	unsigned int id;
	string type;
	aiString path;
};


class Mesh
{
public:
	vector<Vertex> vertices;
	vector<unsigned int> indices;
	vector<Texture> textures;
	Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures);
	void draw(Shader shader);
	unsigned int VAO, VBO, EBO;
private:

	void set_up_mesh();

};




