#include<glad/glad.h>
#include"Model.h"
#include"assimp\Importer.hpp"
#include"assimp\scene.h"
#include"assimp\postprocess.h"
#include<iostream>
#include"glm.hpp"
#include"tools/stb_image.h"
#include<glad/glad.h>
#include"assimp\postprocess.h"

unsigned int TextureFromFile(const char* path, string& directory)
{
	unsigned int texture;
	glGenTextures(1, &texture);
	//绑定
	glBindTexture(GL_TEXTURE_2D, texture);

	// 为当前绑定的纹理对象设置环绕、过滤方式
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


	string _path = "res/objects/" + string(path);
	//nrChannels颜色通道个数
	int width, height, nrChannels;
	unsigned char* data = stbi_load(_path.c_str(), &width, &height, &nrChannels, 0);
	if (data)
	{
		//设置 GL_RED GL_RGB GL_RGBA
		if (_path.find("jpg") == string::npos)
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		else
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		//生成mipmap
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);
	return texture;
}


void Model::load_model(string const& path)
{
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		std::cout << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
		return;
	}
	directory = path.substr(0, path.find_last_of('/'));

	process_node(scene->mRootNode, scene);
}

void Model::process_node(aiNode* node, const aiScene* scene)
{
	// 处理节点所有的网格, 如果有的话
	for (unsigned int i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		meshes.push_back(process_mesh(mesh, scene));
	}
	// 接下来对它的子节点重复这一过程
	for (unsigned int i = 0; i < node->mNumChildren; i++)
	{
		process_node(node->mChildren[i], scene);
	}
}

Mesh Model::process_mesh(aiMesh* mesh, const aiScene* scene)
{
	vector<Vertex> vertices;
	vector<unsigned int> indices;
	vector<Texture> textures;


	for (unsigned int i = 0; i < mesh->mNumVertices; i++)
	{
		Vertex vertex;
		// 处理顶点
		glm::vec3 _position;
		_position.x = mesh->mVertices[i].x;
		_position.y = mesh->mVertices[i].y;
		_position.z = mesh->mVertices[i].z;
		vertex.position = _position;

		//处理法线
		glm::vec3 _normal;
		_normal.x = mesh->mNormals[i].x;
		_normal.y = mesh->mNormals[i].y;
		_normal.z = mesh->mNormals[i].z;
		vertex.normal = _normal;

		//处理纹理
		// 一个模型在一个定点上最多有8个不同的纹理坐标
		glm::vec2 _tex_coords;
		_tex_coords.x = mesh->mTextureCoords[0][i].x;
		_tex_coords.y = mesh->mTextureCoords[0][i].y;
		vertex.tex_coords = _tex_coords;


		vertices.push_back(vertex);
	}

	//处理索引
	for (unsigned int i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];
		for (unsigned int j = 0; j < face.mNumIndices; j++)
			indices.push_back(face.mIndices[j]);
	}

	//处理材质
	if (mesh->mMaterialIndex >= 0)
	{
		aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

		//漫反射
		vector<Texture> diffuseMaps = load_material_texture(material, aiTextureType_DIFFUSE, "texture_diffuse");
		textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

		//镜面反射
		vector<Texture> specularMaps = load_material_texture(material, aiTextureType_SPECULAR, "texture_specular");
		textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());

		// 法线
		std::vector<Texture> normalMaps = load_material_texture(material, aiTextureType_HEIGHT, "texture_normal");
		textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());

		// height maps
		std::vector<Texture> heightMaps = load_material_texture(material, aiTextureType_AMBIENT, "texture_height");
		textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());
	}

	return Mesh(vertices, indices, textures);
}

vector<Texture> Model::load_material_texture(aiMaterial* mat, aiTextureType type, string type_name)
{
	vector<Texture> textures;
	for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
	{
		aiString str;
		mat->GetTexture(type, i, &str);
		bool skip = false;
		for (unsigned int j = 0; j < textures_loaded.size(); j++)
		{

			if (std::strcmp(textures_loaded[i].path.data, str.C_Str()) == 0)
			{
				textures_loaded.push_back(textures_loaded[j]);
				skip = true;
				break;
			}
		}
		if (!skip)
		{
			Texture texture;
			texture.id = TextureFromFile(str.C_Str(), directory);
			texture.type = type_name;
			texture.path = str;
			textures.push_back(texture);
		}
	}
	return textures;
}

void Model::draw(Shader shader)
{
	for (unsigned int i = 0; i < meshes.size(); i++)
		meshes[i].draw(shader);
}
