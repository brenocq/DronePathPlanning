#ifndef MODEL_H
#define MODEL_H

#include <vector>
#include <string>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "mesh.h"
#include "texture.h"

class Model
{
public:
	Model(const std::string& _modelName, const std::string& _fileType);
	~Model();

	void loadModel();
	void renderModel();
	void clearModel();

private:
	void loadNode(aiNode *node, const aiScene *scene);
	void loadMesh(aiMesh *mesh, const aiScene *scene);
	void loadMaterials(const aiScene *scene);

	std::string modelName;
	std::string fileType;
	std::vector<Mesh*> meshList;
	std::vector<Texture*> textureList;
	std::vector<unsigned int> meshToTex;
};
#endif// MODEL_H
