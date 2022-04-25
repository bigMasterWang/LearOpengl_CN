#pragma once
#include<vector>
#include"Mesh.h"
#include"assimp\scene.h"
#include"tools/shader.h"
using namespace std;


class Model
{
public:
	vector<Mesh> meshes;
	vector<Texture> textures_loaded;
private:


	string directory;
	void load_model(string const& path);
	void process_node(aiNode* node, const aiScene* scene);
	Mesh process_mesh(aiMesh* mesh, const aiScene* scene);
	vector<Texture> load_material_texture(aiMaterial* mat, aiTextureType type, string type_name);

public:
	Model(const char* path)
	{
		load_model(path);
	}
	void draw(Shader shader);
};

